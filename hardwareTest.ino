void hardwareTest(){
  //Draw Background
  if(oled_draw_bg ==1 ){
    u8g2.clearBuffer();
    for(int i=0;i<8;i++){
      u8g2.drawLine(i*(127/4), 0, i*(127/4), 127); 
      u8g2.drawLine(0, i*(127/4), 127, i*(127/4)); 
    }
    for (int i=0;i<16;i++){
      u8g2.setCursor((i%4)*(128/4)+1,int(i/4)*(128/4)+10);
      u8g2.print(key[i]);
    }
    u8g2.sendBuffer();
  }
  if(key_pressed == 1){
    for (int i=0;i<16;i++){
      u8g2.setCursor((i%4)*(128/4)+1,int(i/4)*(128/4)+10);
      u8g2.print(key[i]);
    }
    u8g2.sendBuffer();
  }
}
