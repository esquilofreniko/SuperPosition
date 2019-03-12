void MainMenu::run(){
  if(enc1.rotation != 0){
    selected += enc1.rotation;
    if(selected < 0){selected = 0;}
    if(selected > 1){selected = 1;}
    oled.redraw = 1;
  };
  if(oled.redraw == 1){
    oled.clear();
    for(int i=0;i<size;i++){
      if(i==selected){oled.drawText(0,i,1,menu[i].c_str());}
      else{oled.drawText(0,i,0,menu[i].c_str());}
    }
  }
  if(enc1.clicked == 1){
    mode = selected + 1;
    oled.clear();
  }
}
