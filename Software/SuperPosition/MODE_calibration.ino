void Calibration::run(){
  if(oled.redraw == 1){
    oled.clear();
    for(int i=0;i<4;i++){
      String output = "IN" + String(i+1) + " A: " + String(adc.in[i]);
      oled.drawText(0,i,0,output);
      output = " D: " + String(adc.gate[i]);
      oled.drawText(12,i,0,output);
    }
  }
}