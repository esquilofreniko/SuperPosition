void ProbSeq::run(){
  clock();
  controls();
  if(oled.redraw == 1){drawBg();}
}

void ProbSeq::clock(){
  if(midiclock == 1){
    midiclock = 0;
    updatePosition();
    pattMorph(pos);
    output();
    followPos();
    writeNewPosition();
  }
}

void ProbSeq::updatePosition(){
  //Clear Old Position
  if(view == 0){
    if(pos/16 == division){
      drawKey((pos%16)%4,(pos%16)/4);
    }
  }
  if(view == 1){
    if(pos < ((selected+1)*4)+(division*16) && pos >= (selected*4)+(division*16)){
      for(int i=0;i<4;i++){
        drawKey(pos%4,i);
      }
    }
  }
  //Update Position
  pos += 1;
  pos %= length;
}

void ProbSeq::writeNewPosition(){
  //Write New Position
  if(view == 0){
    if(pos/16 == division){
      if(patt[selected][pos] == 0){kp.set(pos%16,6);}
      if(patt[selected][pos] == 1){kp.set(pos%16,3);}
    }
  }
  if(view == 1){
    if(pos < ((selected+1)*4)+(division*16) && pos >= (selected*4)+(division*16)){
      for(int i=0;i<4;i++){
        if(patt[i][pos] == 0){kp.set((pos%4)+(i*4),6);}
        if(patt[i][pos] == 1){kp.set((pos%4)+(i*4),3);}
      }
    }
  }
  kp.show();
}

void ProbSeq::pattMorph(int index){
  //Probability Pattern Morph
  if(morph>random(10)){
    for(int i=0;i<4;i++){
      if(probs[i][index] > random(10)){patt[i][index] = 1;}
      else{patt[i][index] = 0;}
    }
  }
}

void ProbSeq::output(){
  //MIDI Out
  for(int i=0;i<4;i++){
    if(patt[i][pos] == 1){
      usbMIDI.sendNoteOn(60,60,i+4);
    }
    if(patt[i][pos] == 0){
      usbMIDI.sendNoteOff(60,0,i+4);
    }
  }
}

void ProbSeq::controls(){
  if(kp.pressed == 1){
    if(b1.held == 0 && b2.held == 0){
      for(int i=0;i<16;i++){
        if(kp.key[i]==1){
          setStep(i);
        }
      }
    }
  }
  if(b1.clicked== 1){}
  if(b2.clicked== 1){}
  if(b1.held == 1){
    for(int i=0;i<4;i++){
      if(kp.key[i]==1){
        for(int j=0;j<length;j++){
          if(param==0){patt[i][j] = 0;}
          if(param==1){probs[i][j] = 0;}
        }
        drawMatrixLED();
      }
      if(kp.key[i+4]==1){
        for(int j=0;j<length;j++){
          if(param==0){patt[i][j] = 1;}
          if(param==1){probs[i][j] = prob;}
        }
        drawMatrixLED();
      }  
    }
  }
  if(b2.held == 1){}
  if(enc1.clicked == 1){    
    selparam = (selparam + 1)%2;
  }
  if(enc2.clicked == 1){follow = (follow+1)%2;}
  if(enc2.held_t==1){
    view = (view+1)%2;
    drawMatrixLED();
  }
  if(enc1.rotation != 0){
    if(selparam == 0){
      param += enc1.rotation;
      if(param > 2){param = 0;}
      if(param < 0){param = 2;}
    }
    if(selparam == 1){
      if(set == 0){
        if(param == 0){
          morph += enc1.rotation;
          if(morph>10){morph=10;}
          if(morph<0){morph=0;}
        }
        if(param == 1){
          prob += enc1.rotation;
          if(prob>10){prob = 10;}
          if(prob<0){prob = 0;}
        }
        if(param == 2){
          clockDivision += enc1.rotation;
          if(clockDivision > 16){clockDivision=16;}
          if(clockDivision < 0){clockDivision=0;}
        }
      }
    }
    drawMatrixLED();
  }
  if(enc2.rotation != 0){
    selected+= enc2.rotation;
    if(selected>3){selected=0;division++;}
    if(selected<0){selected=3;division--;}
    if(division>3){division=0;}
    if(division<0){division=3;}
    drawMatrixLED();
  }
}

void ProbSeq::setStep(int key){
  if(param == 0){
    if(view == 0){
      patt[selected][key + (division*16)] = (patt[selected][key + (division)*16]+1)%2;
    }
    if(view == 1){
      patt[key/4][((key%4)+(selected*4))+(division*16)] = (patt[key/4][((key%4)+(selected*4))+(division*16)]+1)%2;
    }
  }
  if(param == 1){
    if(view == 0){
      if(probs[selected][key + (division)*16] != prob){probs[selected][key + (division)*16] = prob;}
      else{probs[selected][key + (division)*16] = 0;}
    }
    if(view == 1){
      if(probs[key/4][(key%4)+(selected*4) + (division)*16] != prob){probs[key/4][(key%4)+(selected*4) + (division)*16] = prob;}
      else{probs[key/4][(key%4)+(selected*4) + (division)*16] = 0;}
    }
  }
  if(param == 2){
    if(view == 0){
      if(clockDiv[selected][key + (division)*16] != clockDivision){clockDiv[selected][key + (division)*16] = clockDivision;}
      else{clockDiv[selected][key + (division)*16] = 0;}
    }
    if(view == 1){
      if(clockDiv[key/4][(key%4)+(selected*4) + (division)*16] != clockDivision){clockDiv[key/4][(key%4)+(selected*4) + (division)*16] = clockDivision;}
      else{clockDiv[key/4][(key%4)+(selected*4) + (division)*16] = 0;}
    }
  }
  drawKey((key%16)%4,(key%16)/4);
  kp.show();
}

void ProbSeq::drawBg(){
  oled.clear();
  drawInfo();
  drawDivision();
  if(b1.held || b2.held){drawControls();}
  else{drawMatrix();}
}

void ProbSeq::drawInfo(){
  if(set == 0){
    oled.drawText(0,0,1,"Time");
    if(selparam == 1){if(param == 0){oled.invertedText=1;}}
    oled.drawText(0,1,oled.invertedText,"Mrf:" + dectohex(morph));
    oled.invertedText=0;
    if(selparam == 1){if(param == 1){oled.invertedText=1;}}
    oled.drawText(4,1,oled.invertedText,"Prb:" + dectohex(prob));
    oled.invertedText=0;
    if(selparam == 1){if(param == 2){oled.invertedText=1;}}
    oled.drawText(8,1,oled.invertedText,"Div:" + dectohex(clockDivision));
    oled.invertedText=0;
    if(selparam == 0){
      oled.drawBox(param*32,8,32,8,0);
    }
  }
}

void ProbSeq::drawMatrix(){
  for(int k=0;k<4;k++){
    if(view == 0){
      for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
          oled.invertedText = 0;
          if(((i%4)+(j*4))+(division*16) == pos){oled.invertedText = 1;}
          if(param==0){
            oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(patt[k][(i%4)+(j*4)+(division*16)]));
          }
          if(param==1){
            oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(probs[k][(i%4)+(j*4)+(division*16)]));
          }
          if(param==2){
            oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(clockDiv[k][(i%4)+(j*4)+(division*16)]));
          }
        }
      }
    }
    if(view == 1){
      for(int i=0;i<16;i++){
        oled.invertedText = 0;
        if(pos == i+(division*16)){oled.invertedText = 1;}
        if(param==0){
          oled.drawText(i,k+4,oled.invertedText,dectohexPoint(patt[k][i+(division*16)]));
        }
        if(param==1){
          oled.drawText(i,k+4,oled.invertedText,dectohexPoint(probs[k][i+(division*16)]));
        }
        if(param==2){
          oled.drawText(i,k+4,oled.invertedText,dectohexPoint(clockDiv[k][i+(division*16)]));
        }
      }
    }
    if(k==selected){oled.drawBox(k*32,31,32,33,0);}
  }
}

void ProbSeq::drawControls(){
  if(b1.held == 1){
      oled.drawText(0,4,0,"Clear 1 2 3 4");  
      oled.drawText(0,5,0,"Fill  1 2 3 4");
  }
  if(b2.held == 1){}
}

void ProbSeq::drawKey(int i, int j){
  if(view == 0){
    if(param==0){
      if(patt[selected][(i%4)+(j*4)+(division*16)] == 0){
        kp.set((i%4)+(j*4),0);
      }
      if(patt[selected][(i%4)+(j*4)+(division*16)] == 1){
        kp.set((i%4)+(j*4),1);
      }
    }
    if(param==1){
      if(probs[selected][(i%4)+(j*4)+(division*16)] < prob){
        kp.set((i%4)+(j*4),4);
      }
      if(probs[selected][(i%4)+(j*4)+(division*16)] > prob){
        kp.set((i%4)+(j*4),2);
      }
      if(probs[selected][(i%4)+(j*4)+(division*16)] == prob){
        kp.set((i%4)+(j*4),1);
      }
      if(probs[selected][(i%4)+(j*4)+(division*16)] == 0){
        kp.set((i%4)+(j*4),0);
      }
    }
    if(param==2){
      if(clockDiv[selected][(i%4)+(j*4)+(division*16)] < clockDivision){
        kp.set((i%4)+(j*4),4);
      }
      if(clockDiv[selected][(i%4)+(j*4)+(division*16)] > clockDivision){
        kp.set((i%4)+(j*4),2);
      }
      if(clockDiv[selected][(i%4)+(j*4)+(division*16)] == clockDivision){
        kp.set((i%4)+(j*4),1);
      }
      if(clockDiv[selected][(i%4)+(j*4)+(division*16)] == 0){
        kp.set((i%4)+(j*4),0);
      }
    }
  }
  if(view == 1){
    if(param == 0){
      if(patt[j][i+(selected*4)+(division*16)] == 0){
        kp.set((i%4)+(j*4),0);
      }
      if(patt[j][i+(selected*4)+(division*16)] == 1){
        kp.set((i%4)+(j*4),1);
      }
    }
    if(param == 1){
      if(probs[j][i+(selected*4)+(division*16)] < prob){
        kp.set((i%4)+(j*4),4);
      }
      if(probs[j][i+(selected*4)+(division*16)] > prob){
        kp.set((i%4)+(j*4),2);
      }
      if(probs[j][i+(selected*4)+(division*16)] == prob){
        kp.set((i%4)+(j*4),1);
      }
      if(probs[j][i+(selected*4)+(division*16)] == 0){
        kp.set((i%4)+(j*4),0);
      }
    }
    if(param == 2){
      if(clockDiv[j][i+(selected*4)+(division*16)] < clockDivision){
        kp.set((i%4)+(j*4),4);
      }
      if(clockDiv[j][i+(selected*4)+(division*16)] > clockDivision){
        kp.set((i%4)+(j*4),2);
      }
      if(clockDiv[j][i+(selected*4)+(division*16)] == clockDivision){
        kp.set((i%4)+(j*4),1);
      }
      if(clockDiv[j][i+(selected*4)+(division*16)] == 0){
        kp.set((i%4)+(j*4),0);
      }
    }
  }
}

void ProbSeq::drawMatrixLED(){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      drawKey(i,j);
    }
  }
  writeNewPosition();
  kp.show();
}

void ProbSeq::drawDivision(){
  for(int i=0;i<4;i++){
    if(floor(pos/16)==i){oled.drawText((i*2)+8,3,0,dectohex(i)+".");}
    else{oled.drawText((i*2)+8,3,0,dectohex(i)+" ");}
  }
  oled.drawBox((division*16)+64,24,16,8,0);
}

void ProbSeq::followPos(){
  if(follow == 1){
    if(view == 1){selected = (pos%16)/4;}
    division = (pos%64)/16;
  }
}