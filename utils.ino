String dectohex(int in){
  String out;
  if(in<10){out = String(in);}
  if(in==10){out = "A";}
  if(in==11){out = "B";}
  if(in==12){out = "C";}
  if(in==13){out = "D";}
  if(in==14){out = "E";}
  if(in==15){out = "F";}
  return out;
}
