#include <Arduino.h>
#include "lg240644-s8.h"
#include <MCP23017.h>

#define LED     1
#define LED_ON  digitalWrite(LED,LOW)
#define LED_OFF digitalWrite(LED,HIGH)



MCP23017 mcp[2] = { MCP23017(0x20), MCP23017(0x21) };

void setup() {
    // Set pin mode
    pinMode(LED,OUTPUT);
    Serial.begin(115200);
    Serial.printf("Start...\r\n");
    Wire.begin();
    mcp[0].init();
    mcp[1].init();

	lcd_init();		
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

    lcd_main();
}
