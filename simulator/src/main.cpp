#include <Arduino.h>

#define VALVE1_PIN      5   // pin 34
#define VALVE2_PIN      18  // pin 35
//#define VALVE3_PIN  GPIO  // pin 
#define PUMP_PIN        23  // pin 36

#define LEVEL1_PIN      25  // pin 14
#define LEVEL2_PIN      26  // pin 15
#define LEVEL3_PIN      27  // pin 16
#define LED_PIN         22

void setup() {
    // put your setup code here, to run once:
    pinMode(VALVE1_PIN, INPUT_PULLDOWN);
    pinMode(VALVE2_PIN, INPUT_PULLDOWN);
    pinMode(PUMP_PIN, INPUT_PULLDOWN);
    
    pinMode(LEVEL1_PIN, OUTPUT);
    pinMode(LEVEL2_PIN, OUTPUT);
    pinMode(LEVEL3_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(LEVEL1_PIN, 0);
    digitalWrite(LEVEL2_PIN, 0);
    digitalWrite(LEVEL3_PIN, 0);
    
    digitalWrite(LED_PIN, 0);
}

#define LEVEL_LO    (40*100)
#define LEVEL_MI    (50*100)
#define LEVEL_HI    (60*100)
#define LEVEL_MAX   (100*100) // 100s

uint32_t level = 0;
uint16_t filter = 0;

void loop() {
    // put your main code here, to run repeatedly:
    while(1) {
        if (digitalRead(VALVE1_PIN) || digitalRead(VALVE1_PIN)) {
            if (filter < 10) filter++;
            else {
                digitalWrite(LED_PIN, 0);
                if (level < LEVEL_MAX)
                    level++;
            }
        } else if( digitalRead(PUMP_PIN) ) {
            if(filter < 10) filter--;
            else {
                digitalWrite(LED_PIN, 0);
                if (level > 0)
                    level--;
            }
        } else {
            filter = 0;
            digitalWrite(LED_PIN, 1);
        }
        if (level > LEVEL_LO) digitalWrite(LEVEL1_PIN, 1); else digitalWrite(LEVEL1_PIN, 0);
        if (level > LEVEL_MI) digitalWrite(LEVEL2_PIN, 1); else digitalWrite(LEVEL2_PIN, 0);
        if (level > LEVEL_HI) digitalWrite(LEVEL3_PIN, 1); else digitalWrite(LEVEL3_PIN, 0);
        delay(10);
    }
}