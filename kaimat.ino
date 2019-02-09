//Keypad
#include "Adafruit_NeoTrellis.h"
Adafruit_NeoTrellis trellis;
#include <Wire.h>
bool key [16];
bool key_pressed = 0;
bool key_released = 0;

TrellisCallback blink(keyEvent evt){
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    key[evt.bit.NUM] = 1;
    key_pressed = 1;
//    trellis.pixels.setPixelColor(evt.bit.NUM, trellis.pixels.Color(255,255,255)); 
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
    key[evt.bit.NUM] = 0;
    key_released = 1;
//    trellis.pixels.setPixelColor(evt.bit.NUM, 0); 
  }
//  trellis.pixels.show();
//  return 0;
}

int midiIn_chan = 5;
int midiOut_chan[4] = {1,2,3,4};
int mode = 2;
int oldmode = mode;
int count = 0;
bool oled_draw_bg = 1;

void setup(){
  Serial.begin(9600);
  if (!trellis.begin()) {
    Serial.println("Could not start trellis, check wiring?");
    while(1);
  } else {
    Serial.println("NeoPixel Trellis started");
  }
  for(int i=0; i<16; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }
  midi_init(); 
  hardware_init();
}

void loop(){
  midi_read();
  hardware_read();
  if(oldmode != mode){oled_clear();}
  if(mode == 0){mainMenu();}
  if(mode == 1){midiSetup();}
  if(mode == 2){probSeq();}
  oled_draw_bg = 0;
  oldmode = mode;
  count++;
  count %= 10000;
  delayMicroseconds(10);
}
