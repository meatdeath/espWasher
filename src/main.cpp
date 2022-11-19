#include <Arduino.h>
#include <MCP23017.h>
#include <OneWire.h>
#include <DS18B20.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

#include "lg240644-s8.h"
#include "screens.h"
#include "sw_timers.h"

#define LED     1
#define LED_ON  digitalWrite(LED,LOW)
#define LED_OFF digitalWrite(LED,HIGH)

#define ONE_WIRE_BUS 19

#define BUZER_PORT  GPIO_A
#define BUZER_MASK  0b00010000

#define BUZER_ON()  mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)|BUZER_MASK)
#define BUZER_OFF() mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)&~BUZER_MASK)

#define EXT0_PORTA_INT  13

uint8_t button_state = 0xFF;
// void IRAM_ATTR Ext0PortA() {
//     uint8_t button_state = 0xFF;
// }

MCP23017 mcp[2] = { MCP23017(0x20), MCP23017(0x21) };

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);
MPU6050 mpu6050(Wire);

void setup() {
    // Set pin mode
    pinMode(LED,OUTPUT);
    Serial.begin(115200);
    Serial.printf("Start...\r\n");
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    mcp[0].init();
    mcp[1].init();

    mcp[0].writeRegister(MCP23017Register::IODIR_A,0b11111000);
    mcp[0].writeRegister(MCP23017Register::IODIR_B,0x00);
    // configure interrupt
    // mcp[0].writeRegister(MCP23017Register::GPINTEN_A,0b11111000);   // interrupt on change
    // mcp[0].writeRegister(MCP23017Register::DEFVAL_A,0b11111000);    // default value
    // mcp[0].writeRegister(MCP23017Register::INTCON_A,0b11111000);    // compare with default for interrupt
    mcp[0].writeRegister(MCP23017Register::GPPU_A,0b11111000);      // enable pull-ups

    mcp[1].writeRegister(MCP23017Register::IODIR_A,0x00);
    mcp[1].writeRegister(MCP23017Register::IODIR_B,0x00);

    pinMode(EXT0_PORTA_INT,INPUT_PULLUP);
    //attachInterrupt(EXT0_PORTA_INT, Ext0PortA, FALLING);

    // wait until address found
    if (sensor.begin() == false)
    {
        Serial.println("ERROR: No device found");
        while (!sensor.begin()); // wait until device comes available.
    }

    sensor.setResolution(12);
    sensor.setConfig(DS18B20_CRC);  // or 1
    sensor.requestTemperatures();

	lcd_init();	
    lcd_clr_screen();
    screen_main(0);
    swTimerInit();
}

uint8_t wash_mode_index = 0;

#define BUTTON_MASK_UP      0b10000000
#define BUTTON_MASK_RIGHT   0b01000000
#define BUTTON_MASK_LEFT    0b00100000
#define BUTTON_MASK_DOWN    0b00010000
#define BUTTON_MASK_START   0b00001000

enum mode_en {
    MODE_MAIN_MENU = 0,
    MODE_PREVIEW,
    MODE_EDIT
};

uint8_t mode = MODE_MAIN_MENU;

#define BUTTON_FILTER_LIMIT 20


void loop() {
    static uint8_t button_last_state = 0;
    static uint8_t button_filter = 0;
    static bool redraw = true;
    static float old_temperature = -273;
    //static uint8_t long_press_cnt = 0;

    
    mpu6050.update();
    if(swTimerIsTriggered(SW_TIMER_ACCELEROMETER_UPDATE,true)) {
        Serial.println("=======================================================");
        if(sensor.isConversionComplete()) {
            float t = sensor.getTempC();
            if (t == DEVICE_CRC_ERROR) {
                Serial.println("DS18B20 CRC error!");
            } else {//if((t-old_temperature) > 0.1 || (t-old_temperature) < -0.1) {
                Serial.printf("Temperature: %3.1fC\r\n", (double)t);
                old_temperature = t;
            }
            sensor.requestTemperatures();
        }
        Serial.print("temp : ");Serial.println(mpu6050.getTemp());
        Serial.print("accX : ");Serial.print(mpu6050.getAccX());
        Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
        Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());

        Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
        Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
        Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());

        Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
        Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());

        Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
        Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
        Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());

        Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
        Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
        Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
        Serial.println("=======================================================\n");
    }

    
    button_state = mcp[0].readPort(MCP23017Port::A);
    if(button_last_state != button_state) {
        button_filter++;
        if(button_filter == BUTTON_FILTER_LIMIT) {
            int beep = 0;
            button_filter = 0;
            button_last_state = button_state;
            Serial.printf("Button state: 0x%02x\r\n", button_state);

            if((button_state&BUTTON_MASK_RIGHT) == 0) { 
                Serial.println("[RIGHT]"); 
                wash_mode_index++; 
                beep = 100;
                if(mode == MODE_PREVIEW) {
                    lcd_clr_screen();
                }
                redraw = true;
            }
            if((button_state&BUTTON_MASK_LEFT)  == 0) { 
                Serial.println("[LEFT]"); 
                wash_mode_index--;
                beep = 100; 
                if(mode == MODE_PREVIEW) {
                    lcd_clr_screen();
                }
                redraw = true;
            }
            if((button_state&BUTTON_MASK_UP)    == 0) { 
                Serial.println("[UP]"); 
                beep = 100; 
                if(mode == MODE_PREVIEW) {
                    mode = MODE_MAIN_MENU;
                    lcd_clr_screen();
                    redraw = true;
                } 
            }
            if((button_state&BUTTON_MASK_DOWN)  == 0) { 
                Serial.println("[DOWN]"); 
                beep = 100;  
                if(mode == MODE_MAIN_MENU) {
                    mode = MODE_PREVIEW;
                    lcd_clr_screen();
                    redraw = true;
                }
            }
            if((button_state&BUTTON_MASK_START) == 0) { 
                Serial.println("[START]"); 
                beep = 500; 
                static uint8_t contrast = 24;
                lcd_set_contrast(contrast);
                Serial.printf("Contrast %d\n", contrast);
                contrast++;
                if(contrast == 32) contrast = 24;
            }

            if(wash_mode_index == WASH_MODE_NUM) wash_mode_index = 0;
            if(wash_mode_index >  WASH_MODE_NUM) wash_mode_index = WASH_MODE_NUM - 1;

            if( beep ) {
                BUZER_ON();
                delay(beep);
                BUZER_OFF();
            }
        }
    }
    if(redraw) {
        //lcd_clr_screen();
        switch(mode) {
            case MODE_MAIN_MENU:
                screen_main(wash_mode_index);
                break;
            case MODE_PREVIEW:
                screen_preview(wash_mode_index);
                break;
        }
        redraw = false;
    }
}
