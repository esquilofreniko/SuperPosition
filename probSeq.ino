int pS_selected = 0;
int pS_selected_old = -1;

void probSeq(){
  if(oled_draw_bg ==1 ){pS_selected_old = pS_selected+1;};
  //DrawFrame
  if(enc_status != 0){pS_selected += enc_status;};
  if(pS_selected < 0){pS_selected = 3;};
  if(pS_selected > 3){pS_selected = 0;};
  if(pS_selected_old != pS_selected){
    u8g2.clearBuffer();
    if(pS_selected == 0){u8g2.drawFrame(0,0,(128/2)-1,(128/2)-1);};
    if(pS_selected == 1){u8g2.drawFrame((128/2),0,(128/2)-1,(128/2)-1);};
    if(pS_selected == 2){u8g2.drawFrame(0,(128/2),(128/2)-1,(128/2)-1);};
    if(pS_selected == 3){u8g2.drawFrame((128/2),(128/2),(128/2)-1,(128/2)-1);};
    oled_draw_bg = 1;
  }
  //Draw Background
  if(oled_draw_bg ==1 ){
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
  if(key_pressed == 1){
    for (int i=0;i<16;i++){
      u8g2.setCursor((i%4)*(128/8)+1,int(i/4)*(128/8)+10);
      u8g2.print(dectohex(key[i]));
    }
    u8g2.sendBuffer();
  }
  pS_selected_old = pS_selected;
}
