//Inputs
ADC::ADC(byte _pin1,byte _pin2,byte _pin3,byte _pin4):
  pin1(_pin1),
  pin2(_pin2),
  pin3(_pin3),
  pin4(_pin4)
{};

void ADC::init(){
  pin[0] = pin1;
  pin[1] = pin2;
  pin[2] = pin3;
  pin[3] = pin4;
  for(int i=0;i<4;i++){
    gate[4] = 0;
    _gate[4] = 0;
    pinMode(pin[i],INPUT);
  }
};

void ADC::read(){
  for(int i=3;i>-1;i--){
    trig[i] = 0;
    avg[i][avgCounter] = analogRead(pin[i]);
    gate[i] = digitalRead(pin[i]);
    if(gate[i] == 1 && _gate[i]==0){trig[i] = 1;}
    _gate[i] = gate[i];
  }
  avgCounter++;
  avgCounter %= avgMax;
  if(avgCounter == 0){    
    for(int i=3;i>-1;i--){
      in[i] = 0;
      for(int j=0;j<avgMax;j++){
        in[i] += avg[i][j];
      }
      in[i] = in[i] / avgMax;
    }
  }
};

//Digital Outputs
Gate::Gate(byte _pin1,byte _pin2,byte _pin3,byte _pin4):
  pin1(_pin1),
  pin2(_pin2),
  pin3(_pin3),
  pin4(_pin4)
{};

void Gate::init(){
  pin[0] = pin1;
  pin[1] = pin2;
  pin[2] = pin3;
  pin[3] = pin4;
  for(int i=0;i<4;i++){
    pinMode(pin[i],OUTPUT);
    digitalWrite(pin[i],0);
  };
}

void Gate::read(){
  for(int i=0;i<4;i++){
    if(trigger[i] == 1){
      if(val[i] == 1 && prev[i] == 0){
        trigStart = millis();
      }
      else if (val[i] == 1 && prev[i] == 1){
        if(millis() - trigStart > trigTime){
          digitalWrite(pin[i],0);
          val[i] = 0;
        }
      }
      prev[i] = val[i];
    }
  }
}

void Gate::write(byte channel, bool _val){
  digitalWrite(pin[channel],_val);
  val[channel] = _val;
}

//Analog Outputs
DAC::DAC(SP_MCP4922 _a1,SP_MCP4922 _a2,SP_MCP4922 _a3,SP_MCP4922 _a4):
a1(_a1),
a2(_a2),
a3(_a3),
a4(_a4)
{};

void DAC::init(){
  a1.setValue(0);
  a2.setValue(0);
  a3.setValue(0);
  a4.setValue(0);
};

void DAC::write(byte channel, float voltage){
  voltage = voltage * 0.99; //1k Output Resistor
  // if(voltage != 0){
  //   if(channel == 0){
  //     voltage += 0.012;
  //   }
  //   else if(channel == 1){
  //     voltage += 0.015;
  //   }
  //   else if(channel == 2){
  //     voltage += 0;
  //   }
  //   else if(channel == 3){
  //     voltage += 0.009;
  //   }
  // }
  int output = map(voltage,0,10,0,4095);
  if(channel == 0){
    a1.setValue(output);
  }
  else if(channel == 1){
    a2.setValue(output);
  }
  else if(channel == 2){
    a3.setValue(output);
  }
  else if(channel == 3){
    a4.setValue(output);
  }
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
  held_t = 0;
  bool prevHeld = held;
  int prevState = state;
  state = digitalRead(pin);
  if (prevState == 1 && state == 0){buttonDownMs = millis();}
  if (prevState == 0 && state == 1) {
    if (millis() - buttonDownMs < 25) {}
    else if (millis() - buttonDownMs < 500) {clicked = 1;}
  }
  if(state == 0){
    if(millis()-buttonDownMs >= 500){held = 1;}
    if(prevHeld == 0 && held == 1){held_t = 1;}
  }
  else if(state == 1){held = 0;}
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
  held_t = 0;
  bool prevHeld = held;
  int prevState = state;
  state = digitalRead(pinButton);
  if (prevState == 1 && state == 0){buttonDownMs = millis();}
  if (prevState == 0 && state == 1) {
    if (millis() - buttonDownMs < 25) {}
    else if (millis() - buttonDownMs < 500) {clicked = 1;}
  }
  if(state == 0){
    if(millis()-buttonDownMs >= 500){held = 1;}
    if(prevHeld == 0 && held == 1){held_t = 1;}
  }
  else if(state == 1){held = 0;}
}

//KeyMatrix
TrellisCallback blink(keyEvent evt){
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    kp.key[rotate1(evt.bit.NUM)] = 1;
    kp.pressed = 1;
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
    kp.key[rotate1(evt.bit.NUM)] = 0;
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
  pos = rotate2(pos);
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
  display.setFont(0);
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
  display.setCursor((x*8)+1,y*8);
  display.println(text);
}

void Display::drawBox(int x, int y, int boxwidth, int boxheight, bool fill){
  if(fill == 0){display.drawRect(x,y,boxwidth,boxheight,WHITE);}
  if(fill == 1){display.fillRect(x,y,boxwidth,boxheight,WHITE);}
}

void Display::setTextSize(int size){
  display.setTextSize(size);
}
void Display::setFont(int font){
  display.setFont();
}

//Global Functions
void hardware_init(){
  pinMode(ENC1PINA, INPUT_PULLUP);
  pinMode(ENC1PINB, INPUT_PULLUP);
  pinMode(ENC2PINA, INPUT_PULLUP);
  pinMode(ENC2PINB, INPUT_PULLUP);
  adc.init();
  gate.init();
  dac.init();
  oled.init();
  kp.init();
  b1.init();
  b2.init();
  enc1.init();
  enc2.init();
}

void hardware_read(){
  adc.read();
  gate.read();
  b1.read();
  b2.read();
  enc1.read();
  enc2.read();
  kp.read();
  if(enc1.held_t == 1){mode = 0;}
}
