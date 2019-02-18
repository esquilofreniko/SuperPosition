const byte b1pin = 17;
const byte b2pin = 12;

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

Button b1(b1pin);
Button b2(b2pin);

void button_init(){
  b1.init();
  b2.init();
}

void button_read(){
  b1.read();
  b2.read();
}
