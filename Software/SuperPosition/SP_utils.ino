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