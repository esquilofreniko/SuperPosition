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

String dectohex(int in){
  String out;
  if(in<10){out = String(in);}
  else if(in==10){out = "A";}
  else if(in==11){out = "B";}
  else if(in==12){out = "C";}
  else if(in==13){out = "D";}
  else if(in==14){out = "E";}
  else if(in==15){out = "F";}
  else if(in==16){out = "G";}
  else{out = in;}
  return out;
}

String dectohexPoint(int in){
  String out;
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