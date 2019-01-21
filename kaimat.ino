int mode = 1;
int oldmode = mode;
int oled_draw_bg = 1;

void setup(){
  Serial.begin(9600); 
  hardware_init();
}

void loop(){
  delay(50); 
  if(oldmode != mode){oled_draw_bg = 1;};
  keypad_readKeys();
  if(mode == 1){mode1(oled_draw_bg);};
  oled_draw_bg = 0;
  oldmode = mode;
}
