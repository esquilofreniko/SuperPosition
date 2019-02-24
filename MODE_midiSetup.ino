int midiIn_chan = 5;
int midiOut_chan[4] = {1,2,3,4};

void midiSetup(){
  if(oled.redraw == 1){
    oled.clear();
    for(int i=0;i<4;i++){
      oled.drawText(0,i,0,String("MIDIOut" + String(i+1) + ": " + dectohex(midiOut_chan[i])).c_str());
    }
    oled.drawText(0,4,0,String("MIDI_In1: " + dectohex(midiIn_chan)).c_str());
  }
}

int midiclock = 0;

void midi_init() {
  usbMIDI.setHandleNoteOn(myNoteOn);
}

void midi_read() {
  usbMIDI.read();
}

void myNoteOn(byte channel, byte note, byte velocity) {
  midiclock = 0;
  if(channel == 5){
    midiclock = 1;
  }
}
