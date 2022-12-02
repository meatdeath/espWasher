#include <Arduino.h>
#include <MCP23017.h>
#include <OneWire.h>
#include <DS18B20.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

#include "lg240644-s8.h"
#include "common.h"
#include "screens.h"
#include "sw_timers.h"
#include "program.h"

#define LED     1
#define LED_ON  digitalWrite(LED,LOW)
#define LED_OFF digitalWrite(LED,HIGH)

#define ONE_WIRE_BUS 19

#define BUZER_PORT  GPIO_A
#define BUZER_MASK  0b00010000

#define BUZER_ON()  mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)|BUZER_MASK)
#define BUZER_OFF() mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)&~BUZER_MASK)

#define EXT0_PORTA_INT  13

uint16_t button_state = 0xFF;
// void IRAM_ATTR Ext0PortA() {
//     uint8_t button_state = 0xFF;
// }



#define BUTTON_MASK_CANCEL      (1<<7)
#define BUTTON_MASK_MINUS       (1<<6)
#define BUTTON_MASK_PLUS        (1<<5)
#define BUTTON_MASK_SPIN        (1<<4)
#define BUTTON_MASK_RINSE       (1<<3)
#define BUTTON_MASK_TEMPERATURE (1<<2)
#define BUTTON_MASK_WASH        (1<<1)
#define BUTTON_MASK_PREWASH     (1<<0)
#define BUTTON_MASK_START       (1<<8)


uint8_t wash_mode_index = 0;
uint8_t screen_index = SCREEN_MAIN_MENU;
volatile bool scr_redraw = true;
bool scr_clear = true;

MCP23017 mcp[2] = { MCP23017(0x20), MCP23017(0x21) };

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);
MPU6050 mpu6050(Wire);
void NextScreen();

extern wash_setup_t wash_setup[WASH_MODE_NUM];

void setup() {
    // Set pin mode
    pinMode(LED,OUTPUT);
    Serial.begin(115200);
    Serial.printf("Start...\r\n");
    Wire.begin();

	lcd_init();	
    lcd_clr_screen();
    lcd_print_font(90, 24, "Starting...",  &font[FONT_SMALL], 15, 0);

    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    mcp[0].init();
    mcp[1].init();

    mcp[0].writeRegister(MCP23017Register::IODIR_A,0xFF);
    mcp[0].writeRegister(MCP23017Register::IODIR_B,0x01);
    // configure interrupt
    // mcp[0].writeRegister(MCP23017Register::GPINTEN_A,0b11111000);   // interrupt on change
    // mcp[0].writeRegister(MCP23017Register::DEFVAL_A,0b11111000);    // default value
    // mcp[0].writeRegister(MCP23017Register::INTCON_A,0b11111000);    // compare with default for interrupt
    mcp[0].writeRegister(MCP23017Register::GPPU_A,0xFF);      // enable pull-ups
    mcp[0].writeRegister(MCP23017Register::GPPU_B,0x01);      // enable pull-ups

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

    lcd_clr_screen();
    screen_main(wash_mode_index);
    
    swTimerInit();
}


#define BUTTON_FILTER_LIMIT 2


void loop() {
    static uint16_t button_last_state = 0;
    static uint8_t button_filter = 0;
    static float old_temperature = -273;
    uint16_t beep = 0;
    
    mpu6050.update();
    //if(swTimerIsTriggered(SW_TIMER_ACCELEROMETER_UPDATE,true)) {
    if(0){
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

    if(swTimerIsTriggered(SW_TIMER_READ_PORT_A, true)) {
        uint16_t new_button_state = mcp[0].readPort(MCP23017Port::B);
        new_button_state <<= 8;
        new_button_state |= mcp[0].readPort(MCP23017Port::A);
        if(button_state != new_button_state) button_filter = 0;
        button_state = new_button_state;
        if(button_last_state != button_state) {
            button_filter++;
            if(button_filter == BUTTON_FILTER_LIMIT) {
                button_filter = 0;
                button_last_state = button_state;
                Serial.printf("Button state: 0x%02x\r\n", button_state);

                if((button_state&BUTTON_MASK_PLUS) == 0) { 
                    Serial.println("[PLUS]"); 
                    beep = 100;
                    scr_redraw = true;
                    scr_clear = true;
                    switch(screen_index) {
                        case SCREEN_MAIN_MENU:
                            wash_mode_index++;
                            if(wash_mode_index == WASH_MODE_NUM) 
                                wash_mode_index = 0;
                            break;
                        case SCREEN_PREVIEW: scr_redraw = false; scr_clear = false; break;
                    }
                }

                if((button_state&BUTTON_MASK_MINUS)  == 0) { 
                    Serial.println("[MINUS]"); 
                    beep = 100;
                    scr_redraw = true;
                    scr_clear = true;
                    switch(screen_index) {
                        case SCREEN_MAIN_MENU:
                            if(wash_mode_index == 0)
                                wash_mode_index = WASH_MODE_NUM - 1;
                            else
                                wash_mode_index--;
                            break;
                        case SCREEN_PREVIEW: scr_redraw = false; scr_clear = false; break;
                    }
                    scr_redraw = true;
                }

                if((button_state&BUTTON_MASK_CANCEL)    == 0) { 
                    Serial.println("[CANCEL]"); 
                    beep = 100; 
                    scr_redraw = true;
                    scr_clear = true;
                    switch(screen_index) {
                        case SCREEN_MAIN_MENU: scr_redraw = false; scr_clear = false; break;
                        case SCREEN_PREVIEW:
                            screen_index = SCREEN_MAIN_MENU;
                            break;
                    }
                }

                if((button_state&BUTTON_MASK_START)  == 0) { 
                    Serial.println("[START]"); 
                    beep = 100;  
                    screen_index = SCREEN_PREVIEW;
                    scr_clear = true;
                    scr_redraw = true;
                }

                if((button_state&BUTTON_MASK_PREWASH) == 0) {
                    Serial.println("[PREWASH]");
                    beep = 100;
                    scr_clear = false;
                    scr_redraw = true;
                    if (screen_index == SCREEN_PREVIEW && wash_mode_index <= WASH_MODE_INTENSIVE) {
                        if(wash_setup[wash_mode_index].prewash_time_idx < (PREWASH_PARAM_STR_NUM-1))
                            wash_setup[wash_mode_index].prewash_time_idx++;
                        else
                            wash_setup[wash_mode_index].prewash_time_idx = 0;
                    }
                }

                if((button_state&BUTTON_MASK_WASH) == 0) {
                    Serial.println("[WASH]");
                    beep = 100;
                    scr_clear = false;
                    scr_redraw = true;
                    if (screen_index == SCREEN_PREVIEW && wash_mode_index <= WASH_MODE_INTENSIVE) {
                        if(wash_setup[wash_mode_index].wash_time_idx < (WASH_PARAM_STR_NUM-1))
                            wash_setup[wash_mode_index].wash_time_idx++; 
                        else
                            wash_setup[wash_mode_index].wash_time_idx = 0;
                    }
                }

                if((button_state&BUTTON_MASK_TEMPERATURE) == 0) {
                    Serial.println("[TEMPERATURE]");
                    beep = 100;
                    scr_clear = false;
                    scr_redraw = true;
                    if (screen_index == SCREEN_PREVIEW && wash_mode_index <= WASH_MODE_INTENSIVE) {
                        if(wash_setup[wash_mode_index].temperature_idx < (TEMPERATURE_PARAM_STR_NUM-1))
                            wash_setup[wash_mode_index].temperature_idx++; 
                        else
                            wash_setup[wash_mode_index].temperature_idx = 0; 
                    }
                }
                
                if((button_state&BUTTON_MASK_RINSE)  == 0) {
                    Serial.println("[RINSE]");
                    beep = 100;
                    scr_clear = false;
                    scr_redraw = true;
                    if (screen_index == SCREEN_PREVIEW && wash_mode_index <= WASH_MODE_RINSE) {
                        if(wash_setup[wash_mode_index].rinse_cnt < (RINSE_PARAM_STR_NUM-1))
                            wash_setup[wash_mode_index].rinse_cnt++; 
                        else
                            wash_setup[wash_mode_index].rinse_cnt = 0; 
                    }
                }

                if((button_state&BUTTON_MASK_SPIN) == 0) {
                    Serial.println("[SPIN]");
                    beep = 100;
                    scr_clear = false;
                    scr_redraw = true;
                    if (screen_index == SCREEN_PREVIEW && wash_mode_index <= WASH_MODE_SPIN) {
                        if(wash_setup[wash_mode_index].spin_rpm_idx < (SPIN_PARAM_STR_NUM-1))
                            wash_setup[wash_mode_index].spin_rpm_idx++; 
                        else
                            wash_setup[wash_mode_index].spin_rpm_idx = 0; 
                    }
                }
            }
        } else {
            button_filter = 0;
        }
    }

    if( beep ) {
        BUZER_ON();
        delay(beep);
        BUZER_OFF();
        beep = 0;
    }

    if (scr_clear) {
        lcd_clr_screen();
        scr_clear = false;
    }
    if(scr_redraw) {
        //lcd_clr_screen();
        switch(screen_index) {
            case SCREEN_MAIN_MENU:
                screen_main(wash_mode_index);
                break;
            case SCREEN_PREVIEW:
                screen_preview(wash_mode_index);
                break;
            // case SCREEN_EDIT_PREWASH_TIME:
            //     screen_edit_prewash_time(wash_mode_index);
            //     break;
            // case SCREEN_EDIT_WASH_TIME:
            //     screen_edit_wash_time(wash_mode_index);
            //     break;
            // case SCREEN_EDIT_TEMPERATURE:
            //     screen_edit_temperature(wash_mode_index);
            //     break;
            // case SCREEN_EDIT_RINSE:
            //     screen_edit_rinse(wash_mode_index);
            //     break;
            // case SCREEN_EDIT_SPIN:
            //     screen_edit_spin(wash_mode_index);
            //     break;
            default:
                screen_index = SCREEN_MAIN_MENU;
                screen_main(wash_mode_index);
        }
        scr_redraw = false;
    }
}

void NextScreen() {
    uint8_t old_idx = screen_index;
    switch(screen_index) {
        case SCREEN_MAIN_MENU:
        case SCREEN_PREVIEW:
        // case SCREEN_EDIT_PREWASH_TIME:
        // case SCREEN_EDIT_WASH_TIME:
        // case SCREEN_EDIT_TEMPERATURE:
        // case SCREEN_EDIT_RINSE:
        //     screen_index++;
        //     break;
        // case SCREEN_EDIT_SPIN:
        //     screen_index = SCREEN_PREVIEW;
        //     break;
        default:
            screen_index = SCREEN_MAIN_MENU;
    }
    if( screen_index != screen_index )
    {
        lcd_clr_screen();
        scr_redraw = true;
    }
}

