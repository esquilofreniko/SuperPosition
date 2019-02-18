#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
const byte enc1button = 0;
const byte enc1pinA = 1;
const byte enc1pinB = 2;
const byte enc2button = 14;
const byte enc2pinA = 15;
const byte enc2pinB = 16;

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

RotaryEncoder enc1(enc1button,Encoder(enc1pinA,enc1pinB));
RotaryEncoder enc2(enc2button,Encoder(enc2pinA,enc2pinB));

void encoder_init(){
  pinMode(enc1pinA, INPUT_PULLUP);
  pinMode(enc1pinB, INPUT_PULLUP);
  pinMode(enc2pinA, INPUT_PULLUP);
  pinMode(enc2pinB, INPUT_PULLUP);
  enc1.init();
  enc2.init();
}

void encoder_read(){
  enc1.read();
  enc2.read();
  if(enc1.held == 1){mode = 0;}
}
