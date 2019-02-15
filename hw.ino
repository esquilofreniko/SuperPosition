void hardware_init(){
  keypad_init();
  oled_init();
  encoder_init();
  button_init();
}

void hardware_read(){
  button_read();
  encoder_read();
  keypad_read();
}
