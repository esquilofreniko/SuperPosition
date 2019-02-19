#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

class RotaryEncoder {
  const byte pinButton;
  bool state;
  unsigned int buttonDownMs;

  public:
  bool clicked;
  bool held;
  bool held_t;
  bool post;
  int pos;
  int rotation;
  Encoder enc;
  
  RotaryEncoder(byte _pinButton, Encoder _enc):
    pinButton(_pinButton),
    enc(_enc)
    {}
  
  void init() {
    pinMode(pinButton,INPUT_PULLUP);
    state = 1;
  }

  void read() {
    //Read Rotation
    rotation = 0;
    if(pos != enc.read()){pos = enc.read();}
    if(pos > 3 || pos < -3){
      enc.write(0);
      post = 1;
    }
    if(post = 1){
      if(pos > 3){rotation = -1;}
      if(pos < -3){rotation = 1;}
      Serial.println(enc.read());
      post = 0;
    }
    //Read Button
    clicked = 0;
    bool prevHeld = held;
    held = 0;
    held_t = 0;
    int prevState = state;
    state = digitalRead(pinButton);
    if (prevState == 1 && state == 0){buttonDownMs = millis();}
    else if (prevState == 0 && state == 1) {
      if (millis() - buttonDownMs < 50) {}
      else if (millis() - buttonDownMs < 1000) {clicked = 1;}
    }
    if(state == 0){
      if(millis()-buttonDownMs >= 1000){held = 1;}
    }
    if(prevHeld == 0 && held == 1){
      held_t = 1;
    }
  }
};
