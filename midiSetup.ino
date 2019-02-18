void midiSetup(){
  if(oled_draw_bg == 1){
    oled_clear();
    for(int i=0;i<4;i++){
      oled_drawText(0,i,0,String("MIDIOut" + String(i+1) + ": " + dectohex(midiOut_chan[i])).c_str());
    }
    oled_drawText(0,4,0,String("MIDI_In1: " + dectohex(midiIn_chan)).c_str());
    oled_show();
  }
}
