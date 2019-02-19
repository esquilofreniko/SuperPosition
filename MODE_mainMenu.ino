int mM_selected = 0;
const int mM_size = 2;
String mM_menu[mM_size] = {"MIDI Setup", "Prob Seq"};

void mainMenu(){
  if(enc1.rotation != 0){
    mM_selected += enc1.rotation;
    if(mM_selected < 0){mM_selected = 0;}
    if(mM_selected > 1){mM_selected = 1;}
    oled_draw_bg = 1;
  };
  if(oled_draw_bg == 1){
    oled.clear();
    for(int i=0;i<mM_size;i++){
      if(i==mM_selected){oled.drawText(0,i,1,mM_menu[i].c_str());}
      else{oled.drawText(0,i,0,mM_menu[i].c_str());}
    }
  }
  if(enc1.clicked == 1){
    mode = mM_selected + 1;
    oled.clear();
  }
}
