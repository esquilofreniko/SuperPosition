#include "SP_hardware.h"
#include "SP_MODE.h"
int mode = 2;
int oldmode = mode;

void setup(){
  // midi_init();
  hardware_init();
}

void loop(){
  // midi_read();
  hardware_read();
  if(mode == 0){mainMenu.run();}
  if(mode == 1){midiSetup();}
  if(mode == 2){gen.run();}
  if(oled.redraw == 1){oled.show();oled.redraw = 0;}
  if(millis() - oled.lastRedrawMS > 50){
    oled.clear();
    oled.redraw = 1;
    oled.lastRedrawMS = millis();
  }
  if(oldmode != mode){oled.clear();oled.redraw=1;oldmode=mode;}
}
