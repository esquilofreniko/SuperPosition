int midiclock = 0;

void midi_init() {
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
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

void myNoteOff(byte channel, byte note, byte velocity) {
}

//  Serial.print("Note On, ch=");
//  Serial.print(channel, DEC);
//  Serial.print(", note=");
//  Serial.print(note, DEC);
//  Serial.print(", velocity=");
//  Serial.println(velocity, DEC);
