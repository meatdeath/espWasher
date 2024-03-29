
#include <Arduino.h>
#include <MCP23017.h>
#include <OneWire.h>
#include <DS18B20.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

#include "common.h"
#include "motor_pid.h"
#include "lg240644-s8.h"
#include "screens.h"
#include "sw_timers.h"
#include "program.h"

//---------------------------------------------------------------------------------------

#define LED     1
#define LED_ON  digitalWrite(LED,LOW)
#define LED_OFF digitalWrite(LED,HIGH)

#define ONE_WIRE_BUS 19

#define BUZER_PORT  GPIO_A
#define BUZER_MASK  0b00010000

#define BUZER_ON()  mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)|BUZER_MASK)
#define BUZER_OFF() mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)&~BUZER_MASK)

#define EXT0_PORTA_INT  13

#define BUTTON_MASK_PREWASH     (1<<0)
#define BUTTON_MASK_WASH        (1<<1)
#define BUTTON_MASK_TEMPERATURE (1<<2)
#define BUTTON_MASK_RINSE       (1<<3)
#define BUTTON_MASK_SPIN        (1<<4)
#define BUTTON_MASK_PLUS        (1<<5)
#define BUTTON_MASK_MINUS       (1<<6)
#define BUTTON_MASK_CANCEL      (1<<7)
#define BUTTON_MASK_START       (1<<8)


#define BUTTON_FILTER_LIMIT 2

//#define GYRO_ENABLE

//---------------------------------------------------------------------------------------

MCP23017 mcp[2] = { MCP23017(0x20), MCP23017(0x21) };
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);
#ifdef GYRO_ENABLE
MPU6050 mpu6050(Wire);
#endif

volatile bool scr_redraw = true;
bool scr_clear = true;

uint16_t button_state = 0xFFFF;
uint8_t wash_mode_index = 0;
uint8_t screen_index = SCREEN_MAIN_MENU;

extern wash_setup_t wash_setup[WASH_MODE_NUM];

volatile bool motor_enabled = false;
uint32_t motor_pwm_on_time = 50;

volatile uint32_t synchro_counter = 0;
volatile uint16_t measured_synchro_ticks = 0;
volatile uint32_t measured_rpm = 0;

uint16_t speed_rpm = 0;
uint8_t motor_speed_index = 0;

//---------------------------------------------------------------------------------------

void ZeroCrossing();
void SynchroCounting();

//---------------------------------------------------------------------------------------

// void IRAM_ATTR Ext0PortA() {
//     uint8_t button_state = 0xFF;
// }

void setup() {
    // Set pin mode
    pinMode(LED,OUTPUT);
    Serial.begin(115200);
    Serial.printf("Start...\r\n");
    Wire.begin();

	lcd_init();	
    lcd_clr_screen();
    lcd_print_font(90, 24, "Загрузка...",  &font[FONT_SMALL], 15, 0);

#ifdef GYRO_ENABLE
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
#endif
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

    pinMode(MOTOR_PWM_PIN, OUTPUT);
    digitalWrite(MOTOR_PWM_PIN, 0);
    pinMode(ZC_PIN, INPUT_PULLUP);
    pinMode(SYNCHRO_PIN, INPUT_PULLUP);

    attachInterrupt(ZC_PIN, ZeroCrossing, FALLING);
    attachInterrupt(SYNCHRO_PIN, SynchroCounting, FALLING);

    pidInit(4,0.001,0);
}

//---------------------------------------------------------------------------------------

void loop() {
    static uint16_t button_last_state = 0;
    static uint8_t button_filter = 0;
    static float old_temperature = -273;
    uint16_t beep = 0;
    
    //if(swTimerIsTriggered(SW_TIMER_ACCELEROMETER_UPDATE,true)) {
    if(0){
#ifdef GYRO_ENABLE
        mpu6050.update();
#endif
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

#ifdef GYRO_ENABLE
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
#endif
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
                        case SCREEN_PREVIEW: 
                            scr_redraw = false; 
                            scr_clear = false; 
                            break;
                        case SCREEN_WORKING:
                            if(motor_speed_index < 9)
                            {
                                motor_speed_index++;
                            }
                            break;
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
                        case SCREEN_PREVIEW: 
                            scr_redraw = false; 
                            scr_clear = false; 
                            break;
                        case SCREEN_WORKING:
                            if(motor_speed_index > 1)
                            {
                                motor_speed_index--;
                            }
                            break;
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
                    switch(screen_index)
                    {
                        case SCREEN_MAIN_MENU: 
                            screen_index = SCREEN_PREVIEW; 
                            break;
                        case SCREEN_PREVIEW: 
                            screen_index = SCREEN_WORKING; 
                            motor_pwm_on_time = 10;
                            motor_speed_index = 1;
                            motor_enabled = true; 
                            synchro_counter = 0; 
                            pidReset();
                            break;
                        case SCREEN_WORKING: 
                            if(motor_pwm_on_time < 90)
                            {
                                motor_pwm_on_time += 10;
                            }
                            else
                            {
                                screen_index = SCREEN_PREVIEW; 
                                motor_enabled = false; 
                                digitalWrite(MOTOR_PWM_PIN, 0);
                            }
                            break;
                    } 
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
                            wash_setup[wash_mode_index].wash_time_idx = 1;
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

    if(motor_enabled && swTimerIsTriggered(SW_TIMER_MOTOR_CTL,true)) {
        if (motor_speed_index == 1) speed_rpm = 60;
        if (motor_speed_index == 2) speed_rpm = 120;
        if (motor_speed_index == 3) speed_rpm = 180;
        if (motor_speed_index == 4) speed_rpm = 240;
        if (motor_speed_index == 5) speed_rpm = 300;
        if (motor_speed_index == 6) speed_rpm = 400;
        if (motor_speed_index == 7) speed_rpm = 600;
        if (motor_speed_index == 8) speed_rpm = 800;
        if (motor_speed_index == 9) speed_rpm = 1000;
        double pid_output = pidCompute(RPM_TO_TICKS(speed_rpm)/10, measured_synchro_ticks);
        int32_t corr_output = (int16_t)pid_output;
        if (corr_output <= 0) corr_output = 1;
        if (corr_output > 1000 ) corr_output = 1000;
        motor_pwm_on_time = map(corr_output, 1, RPM_TO_TICKS(1000)/10, 1, 100);
        static char tmp_str[100];
        sprintf(tmp_str, "PID: Set=%d Input= %d Output=%f Corr_Out=%d Pwm=%d", RPM_TO_TICKS(speed_rpm)/10, measured_synchro_ticks, pid_output, corr_output, motor_pwm_on_time);
        Serial.println(tmp_str);
    }

    if(scr_redraw) {
        if (scr_clear) {
            lcd_clr_screen();
            scr_clear = false;
        }
        switch(screen_index) {
            case SCREEN_MAIN_MENU:
                screen_main(wash_mode_index);
                break;
            case SCREEN_PREVIEW:
                screen_preview(wash_mode_index);
                break;
            case SCREEN_WORKING:
                screen_working(wash_mode_index);
                break;
            default:
                screen_index = SCREEN_MAIN_MENU;
                screen_main(wash_mode_index);
        }
        scr_redraw = false;
    }
}

//---------------------------------------------------------------------------------------

void ZeroCrossing() 
{
    if(motor_enabled)
    {
        digitalWrite(MOTOR_PWM_PIN, 1);
        swTimerConfigureUpdateTime(SW_TIMER_MOTOR_PWM, motor_pwm_on_time);
        swTimerStart(SW_TIMER_MOTOR_PWM);
    }
}

void SynchroCounting()
{
    synchro_counter++;
}

//---------------------------------------------------------------------------------------
