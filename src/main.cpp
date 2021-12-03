#include <Arduino.h>
//#include "lg24064-8080.h"
#include "lg240644-s8.h"

#define LED     1
#define LED_ON  digitalWrite(LED,LOW)
#define LED_OFF digitalWrite(LED,HIGH)

void setup() {
  // Set pin mode
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  Serial.printf("Start...\r\n");
		lcd_init();		
}


void loop() {
  // lcd_init2();
  // digitalWrite(LED,LOW);
  // dis_small_pic();
  // digitalWrite(LED,HIGH);
  // delay(500);

  //lcd_test();
  lcd_main();
}
