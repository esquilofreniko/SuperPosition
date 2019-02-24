#include "KM_hardware.h"
int mode = 2;
int oldmode = mode;

void setup(){
  midi_init();
  hardware_init();
}

void loop(){
  midi_read();
  hardware_read();
  if(oldmode != mode){oled.clear();oldmode=mode;}
  if(mode == 0){mainMenu();}
  if(mode == 1){midiSetup();}
  if(mode == 2){probSeq();}
  if(millis() - oled.lastRedrawMS > 50){
    oled.show();
    oled.clear();
    oled.lastRedrawMS = millis();
  }
}
