//OLED
#include <Arduino.h>
#include <U8x8lib.h>
#include <SPI.h>
U8X8_SSD1327_MIDAS_128X128_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void oled_init(){
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_5x7_f);
}

void oled_clear(){
  u8x8.clear();
  oled_draw_bg = 1;
}
