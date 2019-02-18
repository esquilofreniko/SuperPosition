//u8x8
#include <Arduino.h>
#include <U8x8lib.h>
#include <SPI.h>
U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
bool invertedText = 0;

void oled_init(){
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);  
}

void oled_clear(){
  u8x8.clear();
  oled_draw_bg = 1;
}

void oled_drawText(int x,int y, bool inverted, String text){
  if(inverted == 0){u8x8.noInverse();}
  if(inverted == 1){u8x8.inverse();}
  u8x8.setCursor(x,y);
  u8x8.print(text);
}

//ADAFRUIT SSD1306
//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define OLED_RESET  8
//#define OLED_DC     9
//#define OLED_CS     10
//#define OLED_MOSI   11
//#define OLED_CLK   13
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,&SPI,OLED_DC,OLED_RESET,OLED_CS);
//
//void oled_init(){
//if(!display.begin(SSD1306_SWITCHCAPVCC)) {
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;); // Don't proceed, loop forever
//  }
//  display.display();
//}
//
//void oled_clear(){
//  display.clearDisplay();
//  oled_draw_bg = 1;
//}
//
//void oled_show(){
//  display.display();
//}
//
//void oled_drawText(int x, int y, bool inverted, String text){
//  if(inverted == 0){display.setTextColor(WHITE);}
//  if(inverted == 1){display.setTextColor(BLACK,WHITE);}
//  display.setCursor(x*8,y*8);
//  display.println(text);
//}
//
//void oled_drawBox(int x, int y, int boxwidth, int boxheight){
//  display.drawRect(x,y,boxwidth,boxheight,WHITE);
//}
