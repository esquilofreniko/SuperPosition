void hardware_init(){
  button_init();
  encoder_init();
  keypad_init();
  oled_init();
}

void hardware_read(){
  button_read();
  encoder_read();
  keypad_read();
}
