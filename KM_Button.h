class Button {
    const byte pin;
    bool state;
    unsigned int buttonDownMs;

  public:
  bool clicked;
  bool held;
  bool held_t;
  
  Button(byte _pin):
    pin(_pin)
  {}
  
  void init() {
    pinMode(pin, INPUT_PULLUP);
    state = 1;
  }

  void read() {
    clicked = 0;
    bool prevHeld = held;
    held = 0;
    held_t = 0;
    int prevState = state;
    state = digitalRead(pin);
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
