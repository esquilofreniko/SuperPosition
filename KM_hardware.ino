#include "KM_button.h"
#include "KM_encoder.h"
#include "KM_oled.h"
#include "KM_keypad.h"
//Button
#define B1PIN 17
#define B2PIN 12
Button b1(B1PIN);
Button b2(B2PIN);
//Encoder
#define ENC1BUTTON 0
#define ENC1PINA 1
#define ENC1PINB 2
#define ENC2BUTTON 14
#define ENC2PINA 15
#define ENC2PINB 16
RotaryEncoder enc1(ENC1BUTTON,Encoder(ENC1PINA,ENC1PINB));
RotaryEncoder enc2(ENC2BUTTON,Encoder(ENC2PINA,ENC2PINB));
//OLED
#define OLED_RESET  8
#define OLED_DC     9
#define OLED_CS     10
#define OLED_MOSI   11
#define OLED_CLK   13
U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8(OLED_CS,OLED_DC,OLED_RESET);
Display_u8x8 oled(u8x8);
//KeyPad
Adafruit_NeoTrellis trellis;
KeyMatrix kp(trellis);

TrellisCallback blink(keyEvent evt){
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    kp.key[evt.bit.NUM] = 1;
    kp.pressed = 1;
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
    kp.key[evt.bit.NUM] = 0;
    kp.released = 1;
  }
}

void hardware_init(){
  pinMode(ENC1PINA, INPUT_PULLUP);
  pinMode(ENC1PINB, INPUT_PULLUP);
  pinMode(ENC2PINA, INPUT_PULLUP);
  pinMode(ENC2PINB, INPUT_PULLUP);
  b1.init();
  b2.init();
  enc1.init();
  enc2.init();
  kp.init();
  oled.init();
}

void hardware_read(){
  b1.read();
  b2.read();
  enc1.read();
  enc2.read();
  if(enc1.held == 1){mode = 0;}
  kp.read();
}

void oled_clear(){
  oled.clear();
}
