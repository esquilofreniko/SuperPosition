#include "Adafruit_NeoTrellis.h"
//MIDI
int midiIn_chan = 5;
int midiOut_chan[4] = {1,2,3,4};
//Globals
int mode = 2;
int oldmode = mode;
bool oled_draw_bg = 1;

void setup(){
  midi_init(); 
  hardware_init();
}

void loop(){
  midi_read();
  hardware_read();
  if(oldmode != mode){oled_clear();oldmode=mode;}
  if(mode == 0){mainMenu();}
  if(mode == 1){midiSetup();}
  if(mode == 2){probSeq();}
  oled_draw_bg = 0;
}
