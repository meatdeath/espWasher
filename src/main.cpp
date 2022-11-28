#include <Arduino.h>
#include "lg240644-s8.h"
#include "common.h"
#include "screens.h"
#include <MCP23017.h>

#define LED     1
#define LED_ON  digitalWrite(LED,LOW)
#define LED_OFF digitalWrite(LED,HIGH)

#define BUZER_PORT  GPIO_A
#define BUZER_MASK  0b00010000

#define BUZER_ON()  mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)|BUZER_MASK)
#define BUZER_OFF() mcp[1].writeRegister(MCP23017Register::BUZER_PORT, mcp[1].readRegister(MCP23017Register::BUZER_PORT)&~BUZER_MASK)

#define EXT0_PORTA_INT  13

uint8_t button_state = 0xFF;
// void IRAM_ATTR Ext0PortA() {
//     uint8_t button_state = 0xFF;
// }



#define BUTTON_MASK_UP      0b10000000
#define BUTTON_MASK_RIGHT   0b01000000
#define BUTTON_MASK_LEFT    0b00100000
#define BUTTON_MASK_DOWN    0b00010000
#define BUTTON_MASK_START   0b00001000


uint8_t wash_mode_index = 0;
uint8_t screen_index = SCREEN_MAIN_MENU;
static bool scr_redraw = true;
static bool scr_clear = true;

MCP23017 mcp[2] = { MCP23017(0x20), MCP23017(0x21) };

void NextScreen();

void setup() {
    // Set pin mode
    pinMode(LED,OUTPUT);
    Serial.begin(115200);
    Serial.printf("Start...\r\n");
    Wire.begin();
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

	lcd_init();	

    lcd_clr_screen();	
    
    screen_main(wash_mode_index);
}


void loop() {
    // lcd_init2();
    // digitalWrite(LED,LOW);
    // dis_small_pic();
    // digitalWrite(LED,HIGH);
    // delay(500);

    //lcd_test();
    //uint8_t conf = mcp[0].readRegister(MCP23017Register::IODIR_A);
    // mcp[0].writeRegister(MCP23017Register::IODIR_A,0x3F);
    // mcp[0].writeRegister(MCP23017Register::IODIR_B,0x3F);
    // mcp[1].writeRegister(MCP23017Register::IODIR_A,0x3F);
    // mcp[1].writeRegister(MCP23017Register::IODIR_B,0x3F);
    // mcp[0].writeRegister(MCP23017Register::GPIO_A,0xFF);
    // mcp[0].writeRegister(MCP23017Register::GPIO_B,0xFF);
    // mcp[1].writeRegister(MCP23017Register::GPIO_A,0xFF);
    // mcp[1].writeRegister(MCP23017Register::GPIO_B,0xFF);

    // while(1) {
    //     mcp[0].writeRegister(MCP23017Register::GPIO_A,0x3F);
    //     mcp[0].writeRegister(MCP23017Register::GPIO_B,0x3F);
    //     mcp[1].writeRegister(MCP23017Register::GPIO_A,0x3F);
    //     mcp[1].writeRegister(MCP23017Register::GPIO_B,0x3F);
    //     delay(250);
    //     mcp[0].writeRegister(MCP23017Register::GPIO_A,0xFF);

    //     delay(250);
    //     mcp[0].writeRegister(MCP23017Register::GPIO_B,0xFF);

    //     delay(500);
    //     mcp[1].writeRegister(MCP23017Register::GPIO_A,0xFF);
        
    //     delay(1000);
    //     mcp[1].writeRegister(MCP23017Register::GPIO_B,0xFF);
    //     delay(250);

    // }

    if(0)
    {
        uint16_t mask = 0;
        for( int i = 0; i < 16; i++ ) {
            mask <<= 1;
            mask |= 1;
            mcp[1].writeRegister(MCP23017Register::GPIO_A,mask&0xFF);
            mcp[1].writeRegister(MCP23017Register::GPIO_B,(mask>>8)&0xFF);
            delay(250);
        }
        for( int i = 0; i < 16; i++ ) {
            mask <<= 1;
            //mask &= 0xFFFE;
            mcp[1].writeRegister(MCP23017Register::GPIO_A,mask&0xFF);
            mcp[1].writeRegister(MCP23017Register::GPIO_B,(mask>>8)&0xFF);
            delay(250);
        }

        mcp[1].writeRegister(MCP23017Register::GPIO_A,0xFF);
        mcp[1].writeRegister(MCP23017Register::GPIO_B,0xFF);
    }

    //lcd_main();

#define BUTTON_FILTER_LIMIT 20

    static uint8_t button_last_state = 0;
    static uint8_t button_filter = 0;
    //static uint8_t long_press_cnt = 0;
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
                    case SCREEN_EDIT_PREWASH_TIME:
                    case SCREEN_EDIT_WASH_TIME:
                    case SCREEN_EDIT_TEMPERATURE:
                    case SCREEN_EDIT_RINSE:
                    case SCREEN_EDIT_SPIN:
                        scr_clear = false; 
                        SelectNextParam(wash_mode_index);
                        break;
                }
            }
            if((button_state&BUTTON_MASK_LEFT)  == 0) { 
                Serial.println("[LEFT]"); 
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
                    case SCREEN_EDIT_PREWASH_TIME:
                    case SCREEN_EDIT_WASH_TIME:
                    case SCREEN_EDIT_TEMPERATURE:
                    case SCREEN_EDIT_RINSE:
                    case SCREEN_EDIT_SPIN:
                        scr_clear = false; 
                        SelectPrevParam(wash_mode_index);
                        break;
                }
                scr_redraw = true;
            }
            if((button_state&BUTTON_MASK_UP)    == 0) { 
                Serial.println("[UP]"); 
                beep = 100; 
                scr_redraw = true;
                scr_clear = true;
                switch(screen_index) {
                    case SCREEN_MAIN_MENU: scr_redraw = false; scr_clear = false; break;
                    case SCREEN_PREVIEW:
                        screen_index = SCREEN_MAIN_MENU;
                        break;
                    case SCREEN_EDIT_PREWASH_TIME:
                    case SCREEN_EDIT_WASH_TIME:
                    case SCREEN_EDIT_TEMPERATURE:
                    case SCREEN_EDIT_RINSE:
                    case SCREEN_EDIT_SPIN:
                        screen_index = SCREEN_PREVIEW;
                        break;
                }
            }
            if((button_state&BUTTON_MASK_DOWN)  == 0) { 
                Serial.println("[DOWN]"); 
                beep = 100;  
                NextScreen();
                scr_clear = true;
                scr_redraw = true;
            }
            if((button_state&BUTTON_MASK_START) == 0) { Serial.println("[START]"); beep = 500; }


            if( beep ) {
                BUZER_ON();
                delay(beep);
                BUZER_OFF();
            }
        }
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
            case SCREEN_EDIT_PREWASH_TIME:
                screen_edit_prewash_time(wash_mode_index);
                break;
            case SCREEN_EDIT_WASH_TIME:
                screen_edit_wash_time(wash_mode_index);
                break;
            case SCREEN_EDIT_TEMPERATURE:
                screen_edit_temperature(wash_mode_index);
                break;
            case SCREEN_EDIT_RINSE:
                screen_edit_rinse(wash_mode_index);
                break;
            case SCREEN_EDIT_SPIN:
                screen_edit_spin(wash_mode_index);
                break;
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
        case SCREEN_EDIT_PREWASH_TIME:
        case SCREEN_EDIT_WASH_TIME:
        case SCREEN_EDIT_TEMPERATURE:
        case SCREEN_EDIT_RINSE:
            screen_index++;
            break;
        case SCREEN_EDIT_SPIN:
            screen_index = SCREEN_PREVIEW;
            break;
        default:
            screen_index = SCREEN_MAIN_MENU;
    }
    if( screen_index != screen_index )
    {
        lcd_clr_screen();
        scr_redraw = true;
    }
}

