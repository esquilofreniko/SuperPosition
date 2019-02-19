//MIDI
int midiIn_chan = 5;
int midiOut_chan[4] = {1,2,3,4};

void midiSetup(){
  if(oled_draw_bg == 1){
    oled.clear();
    for(int i=0;i<4;i++){
      oled.drawText(0,i,0,String("MIDIOut" + String(i+1) + ": " + dectohex(midiOut_chan[i])).c_str());
    }
    oled.drawText(0,4,0,String("MIDI_In1: " + dectohex(midiIn_chan)).c_str());
  }
}
