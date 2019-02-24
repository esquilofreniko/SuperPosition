#include "KM_hardware.h"
#include "KM_MODE.h"
int mode = 2;
int oldmode = mode;

void setup(){
  midi_init();
  hardware_init();
}

void loop(){
  midi_read();
  hardware_read();
  if(mode == 0){mainMenu.run();}
  if(mode == 1){midiSetup();}
  if(mode == 2){probSeq.run();}
  if(oldmode != mode){oled.clear();oldmode=mode;}
  if(millis() - oled.lastRedrawMS > 50){
    oled.show();
    oled.clear();
    oled.lastRedrawMS = millis();
  }
}
