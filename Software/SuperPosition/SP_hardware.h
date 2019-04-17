//ADC
class ADC {
  private:
  const byte pin1,pin2,pin3,pin4;
  const int avgMax = 100;
  byte pin[4];
  public:
  ADC(byte _pin1,byte _pin2,byte _pin3,byte _pin4);
  int in[4];
  int avg[4][100];
  int avgCounter = 0;
  int trig[4];
  int gate[4];
  int _gate[4];
  int lastSave=0;
  bool printAdc = 0;
  void init();
  void read();
};

#define CVINPIN1 17
#define CVINPIN2 16
#define CVINPIN3 15
#define CVINPIN4 14

ADC adc(CVINPIN1,CVINPIN2,CVINPIN3,CVINPIN4);

//Gate
class Gate{
  private:
  byte pin1,pin2,pin3,pin4;
  public:
  byte pin[4];
  bool val[4];
  bool prev[4];
  bool trigger[4] = {1,1,1,1};
  long trigStart;
  short trigTime = 5;
  Gate(byte _pin1,byte _pin2,byte _pin3,byte _pin4);
  void init();
  void read();
  void write(byte channel, bool _val);
};

#define DPIN1 4
#define DPIN2 5
#define DPIN3 6
#define DPIN4 7
Gate gate(DPIN1,DPIN2,DPIN3,DPIN4);

//DAC
#include "SP_MCP4922.h"
class DAC{
  public:
  SP_MCP4922 a1;
  SP_MCP4922 a2;
  SP_MCP4922 a3;
  SP_MCP4922 a4;
  DAC(SP_MCP4922 _a1,SP_MCP4922 _a2,SP_MCP4922 _a3,SP_MCP4922 _a4);
  int v[4];
  void init();
  void write(byte channel, float voltage);
};

#define dacpin11 27
#define dacpin12 31
#define dacpin21 26
#define dacpin22 30
#define dacpin31 25
#define dacpin32 29
#define dacpin41 24
#define dacpin42 28

SP_MCP4922 _a1(dacpin11,dacpin21,dacpin31,dacpin41,0);    
SP_MCP4922 _a2(dacpin11,dacpin21,dacpin31,dacpin41,1);
SP_MCP4922 _a3(dacpin12,dacpin22,dacpin32,dacpin42,1);
SP_MCP4922 _a4(dacpin12,dacpin22,dacpin32,dacpin42,0);
DAC dac(_a1,_a2,_a3,_a4);

//Buttons
class Button {
  private:
  const byte pin;
  bool state;
  unsigned long buttonDownMs;

  public:
  bool clicked;
  bool held;
  bool held_t;

  Button(byte _pin);
  void init();
  void read();
};

#define B1PIN 20
#define B2PIN 3
Button b1(B1PIN);
Button b2(B2PIN);

//Encoders
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

class RotaryEncoder {
  private:
  Encoder enc;
  const byte pinButton;
  bool state;
  unsigned long buttonDownMs;

  public:
  bool clicked;
  bool held;
  bool held_t;
  bool post;
  short pos;
  short rotation;

  RotaryEncoder(byte _pinButton, Encoder _enc);
  void init();
  void read();
};

#define ENC1BUTTON 0
#define ENC1PINA 1
#define ENC1PINB 2
#define ENC2BUTTON 23
#define ENC2PINA 22
#define ENC2PINB 21
RotaryEncoder enc1(ENC1BUTTON,Encoder(ENC1PINA,ENC1PINB));
RotaryEncoder enc2(ENC2BUTTON,Encoder(ENC2PINA,ENC2PINB));

//KeyMatrix
#include <Wire.h>
#include "Adafruit_NeoTrellis.h"

class KeyMatrix {
  private:
  unsigned long lastMillis = 0;
  Adafruit_NeoTrellis trellis;

  public:
  bool key[16];
  bool pressed = 0;
  bool released = 0;

  KeyMatrix(Adafruit_NeoTrellis _trellis);
  void init();
  void read();
  void show();
  void set(int pos, int color);
};

Adafruit_NeoTrellis trellis;
KeyMatrix kp(trellis);

//OLED Display
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoOblique9pt7b.h>

class Display {
  private:
  Adafruit_SSD1306 display;

  public:
  bool redraw = 0;
  bool invertedText = 0;
  unsigned long lastRedrawMS = 0;

  Display(Adafruit_SSD1306 _display);
  void init();
  void clear();
  void show();
  void drawText(int x, int y, bool inverted, String text);
  void drawBox(int x, int y, int boxwidth, int boxheigh, bool fill);
  void setTextSize(int size);
  void setFont(int font);
};

#define OLED_RESET  8
#define OLED_DC     9
#define OLED_CS     10
#define OLED_MOSI   11
#define OLED_CLK   13
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Display oled(display);