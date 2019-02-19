#include <Wire.h>

class KeyMatrix {
  int count = 0;
  int lastMillis = 0;

  public:
  bool key[16];
  bool pressed = 0;
  bool released = 0;
  Adafruit_NeoTrellis trellis;

  KeyMatrix(Adafruit_NeoTrellis _trellis):
  trellis(_trellis)
  {}

  void init(){
    if (!trellis.begin()) {while(1);}
    for(int i=0; i<16; i++){
      trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
      trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
      trellis.registerCallback(i, blink);
    }
  }

  void read(){
    pressed = 0;
    released = 0;
    count = millis() - lastMillis;
    if(count >= 50){
      trellis.read();
      lastMillis = millis();
    }
  }
  void show(){
    trellis.pixels.show();
  }
  
  void set(int pos, int color){
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
};
