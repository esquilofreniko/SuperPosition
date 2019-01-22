//Keypad
#include <Wire.h>
#include "Adafruit_Trellis.h"
#define numKeys 16
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
int last_key_pressed = -1;
int last_key_released = -1;
bool key [16];
//OLED
#include <Arduino.h>
#include <U8g2lib.h>
#include <U8x8lib.h>
#include <SPI.h>
U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
U8X8_SSD1327_MIDAS_128X128_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

//Encoder
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
const int enc1 = 2;
const int enc2 = 1;
const int encb = 0;
int encPos = 0;
int enc_released = 0;
bool enc_pressed = 0;
bool enc_held = 0;
int enc_held_count = 0;
Encoder myEnc(enc1, enc2);
int enc_post = 0;
int enc_status = 0;
//Buttons
const int b1 = 7;
const int b2 = 12;
int b1_released = 0;
int b2_released = 0;
bool b1_pressed = 0;
bool b2_pressed = 0;
bool b1_held = 0;
bool b2_held = 0;
int b1_held_count = 0;
int b2_held_count = 0;
int held_time = 10000;


void hardware_init(){
  //Keypad
  trellis.begin(0x70);
  for(int i=0;i<16;i++){
    key[i] = 0;
  }
  //OLED
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_5x7_f);
  u8g2.begin();
  u8g2.setFont(u8g2_font_5x7_tr);
  //ENCODER
  pinMode(encb,INPUT_PULLUP);
  pinMode(enc1, INPUT_PULLUP);
  pinMode(enc2, INPUT_PULLUP);
  //Buttons
  pinMode(b1,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);
}

void hardware_read(){
  buttons_read();
  encoder_read();
  keypad_read();
}

void oled_clear(){
  u8g2.clear();
  u8g2.clearBuffer();
  oled_draw_bg = 1;
}

void buttons_read(){
  if((digitalRead(b1)+1)%2 != b1_pressed){
    b1_pressed = (digitalRead(b1)+1)%2;
    if(b1_pressed == 1){b1_released = -1;}
  }
  if((digitalRead(b2)+1)%2 != b2_pressed){
    b2_pressed = (digitalRead(b2)+1)%2;
    if(b2_pressed == 1){b2_released = -1;}
  }
  if(b1_released==1){b1_released = 0;}
  if(b2_released==1){b2_released = 0;}
  if(b1_pressed == 0 && b1_released == -1){b1_released = 1;}
  if(b2_pressed == 0 && b2_released == -1){b2_released = 1;}
  if(b1_pressed == 1){b1_held_count++;}
  else{b1_held = 0; b1_held_count = 0;}
  if(b2_pressed == 1){b2_held_count++;}
  else{b2_held = 0; b2_held_count = 0;}
  if(b1_held_count > held_time){b1_held = 1;b1_released=0;}
  if(b2_held_count > held_time){b2_held = 1;b2_released=0;}
}

void encoder_read(){
  enc_status = 0;
  if((digitalRead(encb)+1)%2 != enc_pressed){
    enc_pressed = (digitalRead(encb)+1)%2;
    if(enc_pressed == 1){enc_released = -1;}
  }
  if(enc_released==1){enc_released = 0;}
  if(enc_pressed == 0 && enc_released == -1){enc_released = 1;}
  if(enc_pressed == 1){enc_held_count++;}
  else{enc_held = 0; enc_held_count = 0;}
  if(enc_held_count > held_time){enc_held = 1;enc_released = 0;}
  if(enc_held == 1){mode = 0;}
  
  if (encPos != myEnc.read()) {
    encPos = myEnc.read();
    if(encPos > 3 || encPos < -3){
      myEnc.write(0);
      enc_post = 1;
    }
  }
  if(enc_post == 1){
    if(encPos > 3){enc_status = 1;}
    if(encPos < -3){enc_status = -1;}
    enc_post = 0;
  }
}

void keypad_read(){
  if(count%500==0){
    if (trellis.readSwitches()) {
      for (uint8_t i=0; i<numKeys; i++) {
        if (trellis.justPressed(i)){
          key[i] = 1;
          key_pressed = 1;
          last_key_pressed = i;
          trellis.setLED(i);
        } 
        if (trellis.justReleased(i)){
          key[i] = 0;
          key_pressed = 1;
          last_key_released = i;
          trellis.clrLED(i);
        }
      }
      trellis.writeDisplay();
    }
  }
}
