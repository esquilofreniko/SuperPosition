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
