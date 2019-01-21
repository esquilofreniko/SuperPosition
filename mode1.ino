int selected = 0;
int selected_old = 1;

void mode1(int oled_draw_bg){
  //DrawFrame
  if(selected_old != selected){
    if(selected == 0){u8g2.drawFrame(0,0,(128/2)-1,(128/2)-1);};
    if(selected == 1){u8g2.drawFrame((128/2),0,(128/2)-1,(128/2)-1);};
    if(selected == 2){u8g2.drawFrame(0,(128/2),(128/2)-1,(128/2)-1);};
    if(selected == 3){u8g2.drawFrame((128/2),(128/2),(128/2)-1,(128/2)-1);};
  }
  //Draw Background
  if(oled_draw_bg ==1 ){
    u8g2.clearBuffer();
    for(int i=0;i<8;i++){
      u8g2.drawLine(i*(128/8)-1, 0, i*(128/8)-1, 128); 
      u8g2.drawLine(0, i*(128/8)-1, 128, i*(128/8)-1); 
    }
    for (int i=0;i<16;i++){
      u8g2.setCursor((i%4)*(128/8)+1,int(i/4)*(128/8)+10);
      u8g2.print(key[i]);
    }
    u8g2.sendBuffer();
  }
  //Read Keys
  if (trellis.readSwitches()) {
    for (uint8_t i=0; i<numKeys; i++) {
      if (trellis.justPressed(i)){
        key[i] = 1;
        trellis.setLED(i);
        u8g2.setCursor((i%4)*(128/8)+1,int(i/4)*(128/8)+10);
        u8g2.print(key[i]);
      } 
      if (trellis.justReleased(i)){
        key[i] = 0;
        trellis.clrLED(i);
        u8g2.setCursor((i%4)*(128/8)+1,int(i/4)*(128/8)+10);
        u8g2.print(key[i]);
      }
    }
    trellis.writeDisplay();
    u8g2.sendBuffer();
  }
  selected_old = selected;
}
