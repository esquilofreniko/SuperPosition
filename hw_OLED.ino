#include <SPI.h>
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8(OLED_CS,OLED_DC,OLED_RESET);

class Display_u8x8 {
  public:
  bool invertedText = 0;
  U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8;
  
  Display_u8x8(U8X8_SSD1306_128X64_NONAME_4W_HW_SPI _u8x8):
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

Display_u8x8 oled(u8x8);

void oled_init(){
  oled.init();
}

void oled_clear(){
  oled.clear();
}
