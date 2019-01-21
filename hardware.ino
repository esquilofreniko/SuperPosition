//Keypad
#include <Wire.h>
#include "Adafruit_Trellis.h"
#define numKeys 16
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

//OLED
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

int key [16];

void hardware_init(){
  //Keypad
  trellis.begin(0x70);
  for(int i=0;i<16;i++){
    key[i] = 0;
  }
  //OLED
  u8g2.begin();
  u8g2.setFont(u8g2_font_5x7_tr);
}

void keypad_readKeys(){
  if (trellis.readSwitches()) {
    for (uint8_t i=0; i<numKeys; i++) {
      if (trellis.justPressed(i)){
        key[i] = 1;
        trellis.setLED(i);
      } 
      if (trellis.justReleased(i)){
        key[i] = 0;
        trellis.clrLED(i);
      }
    }
    trellis.writeDisplay();
  }
}
