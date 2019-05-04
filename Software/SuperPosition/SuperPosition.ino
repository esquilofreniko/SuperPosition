#include "SP_hardware.h"
#include "SP_MODE.h"
int mode = 2;
int oldmode = mode;

void setup(){
  hardware_init();
  // delay(1000);
  // loadPreset();
}

void loop(){
  hardware_read();
  if(mode == 0){mainMenu.run();}
  if(mode == 1){calibration.run();}
  if(mode == 2){gen.run();}
  if(oled.redraw == 1){oled.show();oled.redraw = 0;}
  if(millis() - oled.lastRedrawMS > 50){
    oled.clear();
    oled.redraw = 1;
    oled.lastRedrawMS = millis();
    // kp.show();
  }
  if(oldmode != mode){oled.clear();oled.redraw=1;oldmode=mode;}
}
