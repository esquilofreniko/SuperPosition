int midiIn_chan[4] = {1,2,3,4};
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
//  Serial.print("Note On, ch=");
//  Serial.print(channel, DEC);
//  Serial.print(", note=");
//  Serial.print(note, DEC);
//  Serial.print(", velocity=");
//  Serial.println(velocity, DEC);
  if(channel == 1){
    midiclock = 1;
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
//      Serial.print("Note Off, ch=");
//      Serial.print(channel, DEC);
//      Serial.print(", note=");
//      Serial.print(note, DEC);
//      Serial.print(", velocity=");
//      Serial.println(velocity, DEC);
}
