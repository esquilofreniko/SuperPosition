//ADC
class ADC {
  private:
  const byte pin1,pin2,pin3,pin4;
  int _in[4];
  byte pin[4];
  public:
  ADC(byte _pin1,byte _pin2,byte _pin3,byte _pin4);
  int in[4];
  int trig[4];
  int trigDelay = 5;
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

//DAC
#include <DA8568C.h>

class DAC8568 {
    private:
    DA8568C dac8568;

    public:
    DAC8568(DA8568C _dac);
    void init();
    void set(int channel, float voltage);
};

DA8568C dacInput;
DAC8568 dac(dacInput);

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