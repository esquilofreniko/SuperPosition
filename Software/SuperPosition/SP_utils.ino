#include <EEPROM.h>

void writePreset(){
  for(int i=0;i<64;i++){
    for(int j=0;j<4;j++){
      int t = i + (j*64);
      EEPROM.write(t+(256*0),gen.patt[i][j]);
      EEPROM.write(t+(256*1),gen.probs[i][j]);
      EEPROM.write(t+(256*2),gen.clockDiv[i][j]);
      EEPROM.write(t+(256*3),gen.burst[i][j]);
      EEPROM.write(t+(256*4),gen.burstProb[i][j]);
      EEPROM.write(t+(256*5),gen.eventNote[i][j]);
      EEPROM.write(t+(256*6),gen.eventProbActive[i][j]);
      EEPROM.write(t+(256*7),gen.eventProbMin[i][j]);
      EEPROM.write(t+(256*8),gen.eventProbMax[i][j]);
      EEPROM.write(t+(256*9),gen.eventSlew[i][j]);
    }
  }
  for(int i=0;i<96;i++){
    for(int j=0;j<4;j++){
      int t = i + (j*96);
      EEPROM.write(t+(256*10),gen.eventQuant[i][j]);
    }
  }
  for(int i=0;i<4;i++){
    int t = ((256*10) + (96*4)) + i;
    EEPROM.write(t+(4*0),gen.lengthMin[i]);
    EEPROM.write(t+(4*1),gen.lengthMax[i]);
    EEPROM.write(t+(4*2),gen.eventSizeMin[i]);
    EEPROM.write(t+(4*3),gen.eventSizeMax[i]);
  }
}

void loadPreset(){
  for(int i=0;i<64;i++){
    for(int j=0;j<4;j++){
      int t = i + (j*64);
      gen.patt[i][j] = EEPROM.read(t+(256*0));
      gen.probs[i][j] = EEPROM.read(t+(256*1));
      gen.clockDiv[i][j]= EEPROM.read(t+(256*2));
      gen.burst[i][j] = EEPROM.read(t+(256*3));
      gen.burstProb[i][j] = EEPROM.read(t+(256*4));
      gen.eventNote[i][j] = EEPROM.read(t+(256*5));
      gen.eventProbActive[i][j] = EEPROM.read(t+(256*6));
      gen.eventProbMin[i][j] = EEPROM.read(t+(256*7));
      gen.eventProbMax[i][j] = EEPROM.read(t+(256*8));
      gen.eventSlew[i][j] = EEPROM.read(t+(256*9));
    }
  }
  for(int i=0;i<96;i++){
    for(int j=0;j<4;j++){
      int t = i + (j*96);
      gen.eventQuant[i][j] = EEPROM.read(t+(256*10));
    }
  }
  for(int i=0;i<4;i++){
    int t = ((256*10) + (96*4)) + i;
    gen.lengthMin[i] = EEPROM.read(t+(4*0));
    gen.lengthMax[i] = EEPROM.read(t+(4*1));
    gen.eventSizeMin[i] = EEPROM.read(t+(4*2));
    gen.eventSizeMax[i] = EEPROM.read(t+(4*3));
  }
}

float noteToVolt(int note){
  float vout = note * 0.0833333;
  return vout;
}

int rotate1(int in){
  int out = in;
  if(in == 12){out = 0;}
  else if(in == 8) {out = 1;}
  else if(in == 4) {out = 2;}
  else if(in == 0) {out = 3;}
  else if(in == 13){out = 4;}
  else if(in == 9) {out = 5;}
  else if(in == 5) {out = 6;}
  else if(in == 1) {out = 7;}
  else if(in == 14){out = 8;}
  else if(in == 10){out = 9;}
  else if(in == 6){out = 10;}
  else if(in == 2){out = 11;}
  else if(in== 15){out = 12;}
  else if(in== 11){out = 13;}
  else if(in == 7){out = 14;}
  else if(in == 3){out = 15;}
  return out;
}

int rotate2(int in){
  int out = in;
  if(in==0){out = 12;}
  else if(in==1){out = 8;}
  else if(in==2){out = 4;}
  else if(in==3){out = 0;}
  else if(in==4){out = 13;}
  else if(in==5){out = 9;}
  else if(in==6){out = 5;}
  else if(in==7){out = 1;}
  else if(in==8){out = 14;}
  else if(in==9){out = 10;}
  else if(in==10){out = 6;}
  else if(in==11){out = 2;}
  else if(in==12){out = 15;}
  else if(in==13){out = 11;}
  else if(in==14){out = 7;}
  else if(in==15){out = 3;}
  return out;
}

int limit(int in, int minimum, int maximum){
  int out = in;
  if(in < minimum){out = minimum;}
  else if(in > maximum){out = maximum;}
  return out;
}

String zeroPoint(int in){
  String out = in;
  if(in == 0){out = ".";}
  return out;
}

String boolStringInv(int in){
  String out;
  if(in == 1){out = ".";}
  if(in == 0){out = "x";}
  return out;
}

String boolString(int in){
  String out;
  if(in == 0){out = ".";}
  if(in == 1){out = "x";}
  return out;
}

String probString(int in){
  String out = in;
  if(in==0){out = ".";}
  else if(in==10){out = "A";}
  return out;
}

String slewStringPoint(int in){
  String out = in;
  if (in == 0){out = ".";}
  else if(in == -1){out = "/1";}
  else if(in == -2){out = "/2";}
  else if(in == -3){out = "/3";}
  else if(in == -4){out = "/4";}
  else if(in == -5){out = "/5";}
  else if(in == -6){out = "/6";}
  else if(in == -7){out = "/7";}
  else if(in == -8){out = "/8";}
  return out;
}

String slewString(int in){
  String out = in;
  if(in == -1){out = "/1";}
  else if(in == -2){out = "/2";}
  else if(in == -3){out = "/3";}
  else if(in == -4){out = "/4";}
  else if(in == -5){out = "/5";}
  else if(in == -6){out = "/6";}
  else if(in == -7){out = "/7";}
  else if(in == -8){out = "/8";}
  return out;
}

String dectohex(int in){
  String out = in;
  if(in<10){out = String(in);}
  else if(in==10){out = "A";}
  else if(in==11){out = "B";}
  else if(in==12){out = "C";}
  else if(in==13){out = "D";}
  else if(in==14){out = "E";}
  else if(in==15){out = "F";}
  else if(in==16){out = "G";}
  return out;
}

String dectohexPoint(int in){
  String out = in;
  if(in==0){out = ".";}
  else if(in<10){out = String(in);}
  else if(in==10){out = "A";}
  else if(in==11){out = "B";}
  else if(in==12){out = "C";}
  else if(in==13){out = "D";}
  else if(in==14){out = "E";}
  else if(in==15){out = "F";}
  else if(in==16){out = "G";}
  return out;
}