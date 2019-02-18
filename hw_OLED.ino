#include <U8x8lib.h>
#include <SPI.h>
#define OLED_RESET  8
#define OLED_DC     9
#define OLED_CS     10
#define OLED_MOSI   11
#define OLED_CLK   13
U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RESET);

class Display {
  public:
  bool invertedText = 0;
  U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8;
  
  Display(U8X8_SSD1306_128X64_NONAME_4W_HW_SPI _u8x8):
  u8x8(_u8x8)
  {}
  
  void init(){
    u8x8.begin();
    u8x8.setFont(u8x8_font_chroma48medium8_r);    
  }

  void clear(){
    u8x8.clear();
    oled_draw_bg = 1;
  }

  void drawText(int x, int y, bool inverted, String text){
    if(inverted == 0){u8x8.noInverse();}
    if(inverted == 1){u8x8.inverse();}
    u8x8.setCursor(x,y);
    u8x8.print(text);
  }
};

Display oled(u8x8);

void oled_init(){
  oled.init();
}

void oled_clear(){
  oled.clear();
}
