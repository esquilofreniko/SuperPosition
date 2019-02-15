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

void encoder_init(){
  pinMode(enc1button,INPUT_PULLUP);
  pinMode(enc1pinA, INPUT_PULLUP);
  pinMode(enc1pinB, INPUT_PULLUP);
  pinMode(enc2button,INPUT_PULLUP);
  pinMode(enc2pinA, INPUT_PULLUP);
  pinMode(enc2pinB, INPUT_PULLUP);
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
