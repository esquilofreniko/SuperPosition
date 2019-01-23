void midiSetup(){
  if(oled_draw_bg == 1){
    for(int i=0;i<4;i++){
      u8x8.drawString(0,i,String("MIDIOut" + String(i+1) + ": " + dectohex(midiOut_chan[i])).c_str());
    }
    u8x8.drawString(0,4,String("MIDI_In1: " + dectohex(midiIn_chan)).c_str());
  }
}
