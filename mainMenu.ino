int mM_selected = 0;

void mainMenu(){
  if(enc_status != 0){
    mM_selected += enc_status;
    if(mM_selected < 0){mM_selected = 0;}
    if(mM_selected > 1){mM_selected = 1;}
    oled_draw_bg = 1;
  };
  if(oled_draw_bg == 1){
    u8g2.clearBuffer();
    u8g2.drawFrame(0*(128/8),mM_selected*(128/8),128,15);
    u8g2.setCursor(0*(128/8)+5,0*(128/8)+10);
    u8g2.print("Hardware Test");
    u8g2.setCursor(0*(128/8)+5,1*(128/8)+10);
    u8g2.print("Probability Sequencer");
    u8g2.sendBuffer();
  }
  if(enc_released == 1){
    mode = mM_selected + 1;
    oled_clear();
    oled_draw_bg = 1;
  }
}
