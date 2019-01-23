void midiSetup(){
  if(oled_draw_bg == 1){
    u8x8.drawString(0,0,String("midiIn: " + dectohex(midiIn_chan)).c_str());
  }
}
