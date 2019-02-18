#define B1PIN 17
#define B2PIN 12

#define ENC1BUTTON 0
#define ENC1PINA 1
#define ENC1PINB 2
#define ENC2BUTTON 14
#define ENC2PINA 15
#define ENC2PINB 16

#define OLED_RESET  8
#define OLED_DC     9
#define OLED_CS     10
#define OLED_MOSI   11
#define OLED_CLK   13

void hardware_init(){
  button_init();
  encoder_init();
  keypad_init();
  oled_init();
}

void hardware_read(){
  button_read();
  encoder_read();
  keypad_read();
}
