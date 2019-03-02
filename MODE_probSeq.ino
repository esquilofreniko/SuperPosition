void ProbSeq::run(){
  clock();
  controls();
  if(oled.redraw == 1){drawBg();}
}

void ProbSeq::clock(){
  if(midiclock == 1){
    midiclock = 0;
    updatePosition();
    pattMorph();
    output();
    followPos();
    writeNewPosition();
  }
}

void ProbSeq::updatePosition(){
  //Clear Old Position
  if(view == 0){
    if(pos[selected]/16 == division){
      drawKey((pos[selected]%16)%4,(pos[selected]%16)/4);
    }
  }
  if(view == 1){
    for(int i=0;i<4;i++){
      if(pos[i] < ((selected+1)*4)+(division*16) && pos[i] >= (selected*4)+(division*16)){
        drawKey(pos[i]%4,i);
      }
    }
  }
  for(int p=0;p<4;p++){
    //Update Position
    clockDivOp = clockDiv[p][pos[p]];
    if(clockDivOp==0){clockDivOp=1;}
    clockDivCount[p] += 1;
    clockDivCount[p] %= clockDivOp;
    if(clockDivCount[p]==0){
      pos[p] += 1;
      if(pos[p] > lengthMax[p]){pos[p] = lengthMin[p];}
      pos[p] %= 64;
    }
  }
}

void ProbSeq::writeNewPosition(){
  //Write New Position
  if(view == 0){
    if(pos[selected]/16 == division){
      if(patt[selected][pos[selected]] == 0){kp.set(pos[selected]%16,6);}
      if(patt[selected][pos[selected]] == 1){kp.set(pos[selected]%16,3);}
    }
  }
  if(view == 1){
    for(int i=0;i<4;i++){
      if(pos[i] < ((selected+1)*4)+(division*16) && pos[i] >= (selected*4)+(division*16)){
        if(patt[i][pos[i]] == 0){kp.set((pos[i]%4)+(i*4),6);}
        if(patt[i][pos[i]] == 1){kp.set((pos[i]%4)+(i*4),3);}
      }
    }
  }
  kp.show();
}

void ProbSeq::pattMorph(){
  //Probability Pattern Morph
  if(morph>random(10)){
    for(int i=0;i<4;i++){
      if(clockDivCount[i] == 0){
        if(probs[i][pos[i]] > random(10)){patt[i][pos[i]] = 1;}
        else{patt[i][pos[i]] = 0;}
      }
    }
  }
}

void ProbSeq::output(){
  //MIDI Out
  for(int i=0;i<4;i++){
    if(clockDivCount[i]==0){
      if(patt[i][pos[i]] == 1){
        usbMIDI.sendNoteOn(60,60,i+4);
      }
      if(patt[i][pos[i]] == 0){
       usbMIDI.sendNoteOff(60,0,i+4);
      }
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
  if(b1.clicked== 1){
    for(int i=0;i<4;i++){
      pos[i] = lengthMin[i]-1;
    }
    drawMatrixLED();
  }
  if(b2.clicked== 1){
    set += 1;
    set %= 2;
  }
  if(b1.held == 1){
    for(int i=0;i<4;i++){
      if(kp.key[i]==1){
        for(int j=lengthMin[i];j<=lengthMax[i];j++){
          if(param==0){patt[i][j] = 0;}
          if(param==1){probs[i][j] = 0;}
          if(param==2){clockDiv[i][j] = 0;}
        }
        drawMatrixLED();
      }
      if(kp.key[i+4]==1){
        for(int j=lengthMin[i];j<=lengthMax[i];j++){
          if(param==0){patt[i][j] = 1;}
          if(param==1){probs[i][j] = prob;}
          if(param==2){clockDiv[i][j] = clockDivision;}
        }
        drawMatrixLED();
      }  
    }
  }
  if(b2.held == 1){}
  if(enc1.clicked == 1){}
  if(enc2.clicked == 1){
    selparam = (selparam + 1)%2;
  }
  if(enc2.held_t==1){
    view = (view+1)%2;
    drawMatrixLED();
  }
  if(enc1.rotation != 0){
    selected+= enc1.rotation;
    if(selected>3){
      selected=0;
      division++;
    }
    if(selected<0){
      selected=3;
      division--;
    }
    if(division>3){division=0;}
    if(division<0){division=3;}
    drawMatrixLED();
  }
  if(enc2.rotation != 0){
    if(selparam == 0){
      param += enc2.rotation;
      if(param > 3){param = 0;}
      if(param < 0){param = 3;}
    }
    if(selparam == 1){
      if(set == 0){
        if(param == 0){
          morph += enc2.rotation;
          if(morph>10){morph=10;}
          if(morph<0){morph=0;}
        }
        if(param == 1){
          prob += enc2.rotation;
          if(prob>10){prob = 10;}
          if(prob<1){prob = 1;}
        }
        if(param == 2){
          clockDivision += enc2.rotation;
          if(clockDivision > 16){clockDivision=16;}
          if(clockDivision < 2){clockDivision=2;}
        }
        if(param == 3){
          if(enc2.rotation == 1){lengthSet = 1;}
          if(enc2.rotation == -1){lengthSet = 0;}
        }
      }
    }
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
  if(param == 3){
    if(view == 0){
      if(lengthSet==0){
        lengthMin[selected] = key + (division*16);
      }
      else if(lengthSet==1){
        lengthMax[selected] = key + (division*16);
      }
      if(lengthMin[selected] > lengthMax[selected]){
        temp = lengthMin[selected];
        lengthMin[selected] = lengthMax[selected];
        lengthMax[selected] = temp;
      }
      drawMatrixLED();
    }
    if(view == 1){
      if(lengthSet==0){
        lengthMin[key/4] = (key%4) + (selected*4) + (division*16);
      }
      else if(lengthSet==1){
        lengthMax[key/4] = (key%4) + (selected*4) + (division*16);
      }
      if(lengthMin[key/4] > lengthMax[key/4]){
        temp = lengthMin[key/4];
        lengthMin[key/4] = lengthMax[key/4];
        lengthMax[key/4] = temp;
      }
      drawMatrixLED();
    }
  }
  drawKey((key%16)%4,(key%16)/4);
  kp.show();
}

void ProbSeq::drawBg(){
  oled.clear();
  drawInfo();
  if(b1.held || b2.held){drawControls();}
  else{drawMatrix();}
}

void ProbSeq::drawInfo(){
  if(set == 0){
    oled.drawText(0,0,1,"Time");
    oled.drawText(4,0,0,"Event");
    oled.drawText(8,0,0," Pos:");
    drawDivision();
    if(selparam == 1){if(param == 0){oled.invertedText=1;}}
    oled.drawText(0,1,oled.invertedText,"Mrf:" + dectohex(morph));
    oled.invertedText=0;
    if(selparam == 1){if(param == 1){oled.invertedText=1;}}
    oled.drawText(4,1,oled.invertedText,"Prb:" + dectohex(prob));
    oled.invertedText=0;
    if(selparam == 1){if(param == 2){oled.invertedText=1;}}
    oled.drawText(8,1,oled.invertedText,"Div:" + dectohex(clockDivision));
    oled.invertedText=0;
    if(selparam == 1){if(param==3){oled.invertedText=1;}}
    if(lengthSet == 0){oled.drawText(12,1,oled.invertedText,"Siz:S");}
    if(lengthSet == 1){oled.drawText(12,1,oled.invertedText,"Siz:E");}
    oled.invertedText=0;
    if(selparam == 0){
      oled.drawBox(param*32,8,32,8,0);
    }
  }
  if(set == 1){
    oled.drawText(0,0,0,"Time");
    oled.drawText(4,0,1,"Event");
    oled.drawText(8,0,0," Pos:");
    drawDivision();
  }
}

void ProbSeq::drawMatrix(){
  for(int k=0;k<4;k++){
    if(view == 0){
      for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
          oled.invertedText = 0;
          if(((i%4)+(j*4))+(division*16) == pos[k]){oled.invertedText = 1;}
          if(param==0){
            oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(patt[k][(i%4)+(j*4)+(division*16)]));
          }
          if(param==1){
            oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(probs[k][(i%4)+(j*4)+(division*16)]));
          }
          if(param==2){
            oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(clockDiv[k][(i%4)+(j*4)+(division*16)]));
          }
          if(param==3){
            if((i%4)+(j*4)+(division*16) == lengthMin[k] && (i%4)+(j*4)+(division*16) == lengthMax[k]){
              oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,"A");
            }
            else if((i%4)+(j*4)+(division*16) == lengthMin[k]){oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,"S");}
            else if((i%4)+(j*4)+(division*16) == lengthMax[k]){oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,"E");}
            else{oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,".");}
          }
        }
      }
    }
    if(view == 1){
      for(int i=0;i<16;i++){
        oled.invertedText = 0;
        if(pos[k] == i+(division*16)){oled.invertedText = 1;}
        if(param==0){
          oled.drawText(i,k+4,oled.invertedText,dectohexPoint(patt[k][i+(division*16)]));
        }
        if(param==1){
          oled.drawText(i,k+4,oled.invertedText,dectohexPoint(probs[k][i+(division*16)]));
        }
        if(param==2){
          oled.drawText(i,k+4,oled.invertedText,dectohexPoint(clockDiv[k][i+(division*16)]));
        }
        if(param==3){
            if(i + (division*16) == lengthMin[k] && i + (k*4) + (division*16) == lengthMax[k]){
              oled.drawText(i,k+4,oled.invertedText,"A");
            }
            else if(i + (division*16) == lengthMin[k]){oled.drawText(i,k+4,oled.invertedText,"S");}
            else if(i + (division*16) == lengthMax[k]){oled.drawText(i,k+4,oled.invertedText,"E");}
            else{oled.drawText(i,k+4,oled.invertedText,".");}
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
    if(param==3){
      if(lengthMin[selected] == (i%4)+(j*4) + (division*16)){
        kp.set(lengthMin[selected]%16,4);
      }
      else if(lengthMax[selected] == (i%4)+(j*4) + (division*16)){
        kp.set(lengthMax[selected]%16,2);
      }
      else if((i%4)+(j*4)+(division*16) < lengthMax[selected] && (i%4)+(j*4)+(division*16) > lengthMin[selected]){
        kp.set((i%4)+(j*4),7);
      }
      else{kp.set((i%4)+(j*4),0);}
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
    if(param == 3){
      if(lengthMin[j] == (i%4) + (selected*4) + (division*16)){
        kp.set((i%4)+(j*4),4);
      }
      else if(lengthMax[j] == (i%4) + (selected*4) + (division*16)){
        kp.set((i%4)+(j*4),2);
      }
      else if((i%4) + (selected*4) + (division*16) < lengthMax[j] && (i%4) + (selected*4) + (division*16) > lengthMin[j]){
        kp.set((i%4)+(j*4),7);
      }
      else{kp.set((i%4)+(j*4),0);}
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
    if(i == division){oled.invertedText = 1;}
    oled.drawText((i*1)+12,0,oled.invertedText,dectohex(i));
    oled.invertedText = 0;
  }
}

void ProbSeq::followPos(){
  if(follow == 1){
    if(view == 1){selected = (pos[0]%16)/4;}
    division = (pos[0]%64)/16;
  }
}