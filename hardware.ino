//OLED
#include <Arduino.h>
#include <U8x8lib.h>
#include <SPI.h>
U8X8_SSD1327_MIDAS_128X128_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//Encoder
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
const int enc1button = 0;
const int enc1pinA = 1;
const int enc1pinB = 2;
int enc1Pos = 0;
int enc1_released = 0;
bool enc1_pressed = 0;
bool enc1_held = 0;
int enc1_held_count = 0;
int enc1_post = 0;
int enc1_status = 0;
Encoder enc1(enc1pinA, enc1pinB);
const int enc2button = 14;
const int enc2pinA = 15;
const int enc2pinB = 16;
int enc2Pos = 0;
int enc2_released = 0;
bool enc2_pressed = 0;
bool enc2_held = 0;
int enc2_held_count = 0;
int enc2_post = 0;
int enc2_status = 0;
Encoder enc2(enc2pinA, enc2pinB);
//Buttons
const int b1 = 17;
const int b2 = 12;
int b1_released = 0;
int b2_released = 0;
bool b1_pressed = 0;
bool b2_pressed = 0;
bool b1_held = 0;
bool b2_held = 0;
bool b1_held_old;
bool b2_held_old;
bool b1_held_t;
bool b2_held_t;

int b1_held_count = 0;
int b2_held_count = 0;
int held_time = 20000;


void hardware_init(){
  //OLED
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_5x7_f);
  //ENCODER
  pinMode(enc1button,INPUT_PULLUP);
  pinMode(enc1pinA, INPUT_PULLUP);
  pinMode(enc1pinB, INPUT_PULLUP);
  pinMode(enc2button,INPUT_PULLUP);
  pinMode(enc2pinA, INPUT_PULLUP);
  pinMode(enc2pinB, INPUT_PULLUP);
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
  u8x8.clear();
  oled_draw_bg = 1;
}

void buttons_read(){
  b1_held_t = 0;
  b2_held_t = 0;
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
  if(b1_held_old != b1_held && b1_held == 1){b1_held_t = 1;};
  if(b2_held_old != b2_held && b2_held == 1){b2_held_t = 1;};
  b1_held_old = b1_held;
  b2_held_old = b2_held;
}

void encoder_read(){
  enc1_status = 0;
  if((digitalRead(enc1button)+1)%2 != enc1_pressed){
    enc1_pressed = (digitalRead(enc1button)+1)%2;
    if(enc1_pressed == 1){enc1_released = -1;}
  }
  if(enc1_released==1){enc1_released = 0;}
  if(enc1_pressed == 0 && enc1_released == -1){enc1_released = 1;}
  if(enc1_pressed == 1){enc1_held_count++;}
  else{enc1_held = 0; enc1_held_count = 0;}
  if(enc1_held_count > held_time){enc1_held = 1;enc1_released = 0;}
  
  if(enc1_held == 1){mode = 0;}
  
  if (enc1Pos != enc1.read()) {
    enc1Pos = enc1.read();
    if(enc1Pos > 3 || enc1Pos < -3){
      enc1.write(0);
      enc1_post = 1;
    }
  }
  if(enc1_post == 1){
    if(enc1Pos > 3){enc1_status = -1;}
    if(enc1Pos < -3){enc1_status = 1;}
    enc1_post = 0;
  }

  enc2_status = 0;
  if((digitalRead(enc2button)+1)%2 != enc2_pressed){
    enc2_pressed = (digitalRead(enc2button)+1)%2;
    if(enc2_pressed == 1){enc2_released = -1;}
  }
  if(enc2_released==1){enc2_released = 0;}
  if(enc2_pressed == 0 && enc2_released == -1){enc2_released = 1;}
  if(enc2_pressed == 1){enc2_held_count++;}
  else{enc2_held = 0; enc2_held_count = 0;}
  if(enc2_held_count > held_time){enc2_held = 1;enc2_released = 0;}
  
  if (enc2Pos != enc2.read()) {
    enc2Pos = enc2.read();
    if(enc2Pos > 3 || enc2Pos < -3){
      enc2.write(0);
      enc2_post = 1;
    }
  }
  if(enc2_post == 1){
    if(enc2Pos > 3){enc2_status = -1;}
    if(enc2Pos < -3){enc2_status = 1;}
    enc2_post = 0;
  }
}

void keypad_read(){
  key_pressed = 0;
  key_released = 0;
  if(count%2000==0){
    trellis.read();
  }
}
