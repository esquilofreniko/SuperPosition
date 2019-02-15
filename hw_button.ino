const int b1 = 17;
const int b2 = 12;
int b1_released = 0;
int b2_released = 0;
bool b1_pressed = 0;
bool b2_pressed = 0;
bool b1_held = 0;
bool b2_held = 0;
bool b1_held_old;
bool b2_held_old;
bool b1_held_t;
bool b2_held_t;
int b1_held_count = 0;
int b2_held_count = 0;
int held_time = 20000;

void button_init(){
  pinMode(b1,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);
}

void button_read(){
  b1_held_t = 0;
  b2_held_t = 0;
  if((digitalRead(b1)+1)%2 != b1_pressed){
    b1_pressed = (digitalRead(b1)+1)%2;
    if(b1_pressed == 1){b1_released = -1;}
  }
  if((digitalRead(b2)+1)%2 != b2_pressed){
    b2_pressed = (digitalRead(b2)+1)%2;
    if(b2_pressed == 1){b2_released = -1;}
  }
  if(b1_released==1){b1_released = 0;}
  if(b2_released==1){b2_released = 0;}
  if(b1_pressed == 0 && b1_released == -1){b1_released = 1;}
  if(b2_pressed == 0 && b2_released == -1){b2_released = 1;}
  if(b1_pressed == 1){b1_held_count++;}
  else{b1_held = 0; b1_held_count = 0;}
  if(b2_pressed == 1){b2_held_count++;}
  else{b2_held = 0; b2_held_count = 0;}
  if(b1_held_count > held_time){b1_held = 1;b1_released=0;}
  if(b2_held_count > held_time){b2_held = 1;b2_released=0;}
  if(b1_held_old != b1_held && b1_held == 1){b1_held_t = 1;};
  if(b2_held_old != b2_held && b2_held == 1){b2_held_t = 1;};
  b1_held_old = b1_held;
  b2_held_old = b2_held;
}
