//DAC
DAC8568::DAC8568(DA8568C _dac):
  dac8568(_dac)
{};

void DAC8568::init(){
  dac8568.init();
  dac8568.enable_internal_ref();
};

void DAC8568::set(int channel, float voltage){
  // voltage = 0 // 0V 
  // voltage = 4.435 // 8V
  if(voltage<0){voltage = 0;}
  if(voltage>65535){voltage = 65535;}
  dac8568.write(WRITE_UPDATE_N, channel, voltage);
};

//Buttons
Button::Button(byte _pin):
  pin(_pin)
{};

void Button::init() {
  pinMode(pin, INPUT_PULLUP);
  state = 1;
};

void Button::read() {
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
};

//Encoders
RotaryEncoder::RotaryEncoder(byte _pinButton, Encoder _enc):
  pinButton(_pinButton),
  enc(_enc)
{}

void RotaryEncoder::init() {
  pinMode(pinButton,INPUT_PULLUP);
  state = 1;
}

void RotaryEncoder::read() {
  rotation = 0;
  if(pos != enc.read()){pos = enc.read();}
  if(pos > 3 || pos < -3){
    enc.write(0);
    post = 1;
  }
  if(post = 1){
    if(pos > 3){rotation = -1;}
    if(pos < -3){rotation = 1;}
    post = 0;
  }
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

//KeyMatrix
TrellisCallback blink(keyEvent evt){
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    kp.key[evt.bit.NUM] = 1;
    kp.pressed = 1;
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
    kp.key[evt.bit.NUM] = 0;
    kp.released = 1;
  }
}

KeyMatrix::KeyMatrix(Adafruit_NeoTrellis _trellis):
  trellis(_trellis)
{}

void KeyMatrix::init(){
  if (!trellis.begin()) {while(1);}
  for(int i=0; i<16; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }
}

void KeyMatrix::read(){
  pressed = 0;
  released = 0;
  if(millis() - lastMillis >= 50){
    trellis.read();
    lastMillis = millis();
  }
}

void KeyMatrix::show(){
  trellis.pixels.show();
}

void KeyMatrix::set(int pos, int color){
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

//OLED Display
Display::Display(Adafruit_SSD1306 _display):
  display(_display)
{}  

void Display::init(){
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {for(;;);}
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
}

void Display::clear(){
  display.clearDisplay();
}

void Display::show(){
  display.display();
}

void Display::drawText(int x, int y, bool inverted, String text){
  if(inverted == 0){display.setTextColor(WHITE);}
  if(inverted == 1){display.setTextColor(BLACK,WHITE);}
  display.setCursor(x*8,y*8);
  display.println(text);
}

void Display::drawBox(int x, int y, int boxwidth, int boxheight, bool fill){
  if(fill == 0){display.drawRect(x,y,boxwidth,boxheight,WHITE);}
  if(fill == 1){display.fillRect(x,y,boxwidth,boxheight,WHITE);}
}

//Global Functions
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
  kp.read();
  if(enc1.held == 1){mode = 0;}
}