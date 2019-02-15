//Keypad
Adafruit_NeoTrellis trellis;
#include <Wire.h>
bool key [16];
bool key_pressed = 0;
bool key_released = 0;

void keypad_init(){
  if (!trellis.begin()) {while(1);}
  for(int i=0; i<16; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }
}

TrellisCallback blink(keyEvent evt){
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    key[evt.bit.NUM] = 1;
    key_pressed = 1;
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
    key[evt.bit.NUM] = 0;
    key_released = 1;
  }
}

void keypad_read(){
  key_pressed = 0;
  key_released = 0;
  if(count%2000==0){
    trellis.read();
  }
}

void kp_show(){
  trellis.pixels.show();
}

void kp_set(int pos, int color){
  if(color == 0){
    trellis.pixels.setPixelColor(pos,0);
  }
  else if(color == 1){
    trellis.pixels.setPixelColor(pos,trellis.pixels.Color(10,10,10));
  }
  else if(color == 2){
    trellis.pixels.setPixelColor(pos,trellis.pixels.Color(10,0,0));
  }
  else if(color == 3){
    trellis.pixels.setPixelColor(pos,trellis.pixels.Color(0,10,0));
  }
  else if(color == 4){
    trellis.pixels.setPixelColor(pos,trellis.pixels.Color(0,0,10));
  }
  else if(color == 5){
    trellis.pixels.setPixelColor(pos,trellis.pixels.Color(10,10,0));
  }
  else if(color == 6){
    trellis.pixels.setPixelColor(pos,trellis.pixels.Color(10,0,10));
  }
  else if(color == 7){
    trellis.pixels.setPixelColor(pos,trellis.pixels.Color(0,10,10));
  }
}
