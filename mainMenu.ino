int mM_selected = 0;
const int mM_size = 2;
String mM_menu[mM_size] = {" MIDI Setup ", " Prob Seq "};

void mainMenu(){
  if(enc1_status != 0){
    mM_selected += enc1_status;
    if(mM_selected < 0){mM_selected = 0;}
    if(mM_selected > 1){mM_selected = 1;}
    oled_draw_bg = 1;
  };
  if(oled_draw_bg == 1){
    for(int i=0;i<mM_size;i++){
      if(i==mM_selected){
        u8x8.setInverseFont(1);
      }
      u8x8.drawString(0,i,mM_menu[i].c_str());
      u8x8.setInverseFont(0);
    }
  }
  if(enc1_released == 1){
    mode = mM_selected + 1;
    oled_clear();
  }
}
