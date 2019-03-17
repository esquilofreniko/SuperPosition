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
    if(pos[matrix]/16 == division){
      drawKey(pos[matrix]%16);
    }
  }
  if(view == 1){
    for(int i=0;i<4;i++){
      if(pos[i] < ((matrix+1)*4)+(division*16) && pos[i] >= (matrix*4)+(division*16)){
        drawKey((pos[i]%4)+(i*4));
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
      if(activeNote[p][pos[p]] == 0){
        posNote[p] = pos[p];
      }      
    }
  }
}

void ProbSeq::writeNewPosition(){
  //Write New Position
  if(view == 0){
    if(pos[matrix]/16 == division){
      if(patt[matrix][pos[matrix]] == 0){kp.set(pos[matrix]%16,6);}
      if(patt[matrix][pos[matrix]] == 1){kp.set(pos[matrix]%16,3);}
    }
  }
  if(view == 1){
    for(int i=0;i<4;i++){
      if(pos[i] < ((matrix+1)*4)+(division*16) && pos[i] >= (matrix*4)+(division*16)){
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
    set += 1;
    set %= 2;
    drawMatrixLED();
  }
  if(b2.clicked== 1){
    // division++;
    // division%=4;
    // drawMatrixLED();
  }
  if(b1.held == 1){
    for(int i=0;i<4;i++){
      if(kp.key[i]==1){
        for(int j=lengthMin[i];j<=lengthMax[i];j++){
          if(timeParam==0){patt[i][j] = 0;}
          if(timeParam==1){probs[i][j] = 0;}
          if(timeParam==2){clockDiv[i][j] = 0;}
        }
        drawMatrixLED();
      }
      if(kp.key[i+4]==1){
        for(int j=lengthMin[i];j<=lengthMax[i];j++){
          if(timeParam==0){patt[i][j] = 1;}
          if(timeParam==1){probs[i][j] = prob;}
          if(timeParam==2){clockDiv[i][j] = clockDivision;}
        }
        drawMatrixLED();
      }  
    }
  }
  if(b2.held == 1){}
  if(enc1.clicked == 1){
    for(int i=0;i<4;i++){
      pos[i] = lengthMin[i]-1;
    }
    drawMatrixLED();
  }
  if(enc2.clicked == 1){
    selParam = (selParam + 1)%2;
  }
  if(enc2.held_t==1){
    view = (view+1)%2;
    drawMatrixLED();
  }
  if(enc1.rotation != 0){
    matrix+= enc1.rotation;
    if(matrix>3){
      matrix=0;
    }
    if(matrix<0){
      matrix=3;
    }
    drawMatrixLED();
  }
  if(enc2.rotation != 0){
    if(selParam == 0){
      if(set == 0){
        timeParam += enc2.rotation;
        if(timeParam > 3){timeParam = 0;}
        if(timeParam < 0){timeParam = 3;}
      }
      if(set == 1){
        eventParam += enc2.rotation;
        if(eventParam > 3){eventParam = 0;}
        if(eventParam < 0){eventParam = 3;}
      }
    }
    if(selParam == 1){
      if(set == 0){
        if(timeParam == 0){
          morph += enc2.rotation;
          if(morph>10){morph=10;}
          if(morph<0){morph=0;}
        }
        if(timeParam == 1){
          prob += enc2.rotation;
          if(prob>10){prob = 10;}
          if(prob<1){prob = 1;}
        }
        if(timeParam == 2){
          clockDivision += enc2.rotation;
          if(clockDivision > 16){clockDivision=16;}
          if(clockDivision < 2){clockDivision=2;}
        }
        if(timeParam == 3){
          if(enc2.rotation == 1){lengthSet = 1;}
          if(enc2.rotation == -1){lengthSet = 0;}
        }
      }
      if(set == 1){
        if(eventParam == 0){
          eventType[matrix] += enc2.rotation;
          if(eventType[matrix]<0){eventType[matrix]=0;}
          if(eventType[matrix]>1){eventType[matrix]=1;}
        }
        if(eventParam == 1){
          eventMode[matrix] += enc2.rotation;
          if(eventMode[matrix]<0){eventMode[matrix]=0;}
          if(eventMode[matrix]>1){eventMode[matrix]=1;}
        }
        if(eventParam == 2){
          eventProbMin[matrix] += enc2.rotation;
          if(eventProbMin[matrix]<0){eventProbMin[matrix]=0;}
          if(eventProbMin[matrix]>96){eventProbMin[matrix]=96;}
        }
        if(eventParam == 3){
          eventProbMax[matrix] += enc2.rotation;
          if(eventProbMax[matrix]<0){eventProbMax[matrix]=0;}
          if(eventProbMax[matrix]>96){eventProbMax[matrix]=96;}
        }
      }
    }
    drawMatrixLED();
  }
}

void ProbSeq::setStep(int key){
  if(set == 0){
    if(timeParam == 0){
      if(view == 0){
        patt[matrix][key + (division*16)] = (patt[matrix][key + (division)*16]+1)%2;
      }
      if(view == 1){
        patt[key/4][((key%4)+(matrix*4))+(division*16)] = (patt[key/4][((key%4)+(matrix*4))+(division*16)]+1)%2;
      }
    }
    if(timeParam == 1){
      if(view == 0){
        if(probs[matrix][key + (division)*16] != prob){probs[matrix][key + (division)*16] = prob;}
        else{probs[matrix][key + (division)*16] = 0;}
      }
      if(view == 1){
        if(probs[key/4][(key%4)+(matrix*4) + (division)*16] != prob){probs[key/4][(key%4)+(matrix*4) + (division)*16] = prob;}
        else{probs[key/4][(key%4)+(matrix*4) + (division)*16] = 0;}
      }
    }
    if(timeParam == 2){
      if(view == 0){
        if(clockDiv[matrix][key + (division)*16] != clockDivision){clockDiv[matrix][key + (division)*16] = clockDivision;}
        else{clockDiv[matrix][key + (division)*16] = 0;}
      }
      if(view == 1){
        if(clockDiv[key/4][(key%4)+(matrix*4) + (division)*16] != clockDivision){clockDiv[key/4][(key%4)+(matrix*4) + (division)*16] = clockDivision;}
        else{clockDiv[key/4][(key%4)+(matrix*4) + (division)*16] = 0;}
      }
    }
    if(timeParam == 3){
      if(view == 0){
        if(lengthSet==0){
          lengthMin[matrix] = key + (division*16);
        }
        else if(lengthSet==1){
          lengthMax[matrix] = key + (division*16);
        }
        if(lengthMin[matrix] > lengthMax[matrix]){
          temp = lengthMin[matrix];
          lengthMin[matrix] = lengthMax[matrix];
          lengthMax[matrix] = temp;
        }
        drawMatrixLED();
      }
      if(view == 1){
        if(lengthSet==0){
          lengthMin[key/4] = (key%4) + (matrix*4) + (division*16);
        }
        else if(lengthSet==1){
          lengthMax[key/4] = (key%4) + (matrix*4) + (division*16);
        }
        if(lengthMin[key/4] > lengthMax[key/4]){
          temp = lengthMin[key/4];
          lengthMin[key/4] = lengthMax[key/4];
          lengthMax[key/4] = temp;
        }
        drawMatrixLED();
      }
    }
  }
  if(set == 1){
    activeNote[matrix][key + (division*16)] = (activeNote[matrix][key + (division)*16]+1)%2;    
  }
  drawKey(key);
  kp.show();
}

void ProbSeq::drawBg(){
  oled.clear();
  drawInfo();
  if(b1.held || b2.held){drawControls();}
  else{drawMatrix();}
}

void ProbSeq::drawParams(){
  if(set == 0){
    if(selParam == 1){if(timeParam == 0){oled.invertedText=1;}}
    oled.drawText(0,1,oled.invertedText,"Morph:" + dectohex(morph));
    oled.invertedText=0;
    if(selParam == 1){if(timeParam == 1){oled.invertedText=1;}}
    oled.drawText(8,1,oled.invertedText,"Prob:" + dectohex(prob));
    oled.invertedText=0;
    if(selParam == 1){if(timeParam == 2){oled.invertedText=1;}}
    oled.drawText(0,2,oled.invertedText,"Divid:" + dectohex(clockDivision));
    oled.invertedText=0;
    if(selParam == 1){if(timeParam==3){oled.invertedText=1;}}
    if(lengthSet == 0){oled.drawText(8,2,oled.invertedText,"Size:Start");}
    if(lengthSet == 1){oled.drawText(8,2,oled.invertedText,"Size:End");}
    oled.invertedText=0;
    if(selParam == 0){oled.drawBox((timeParam%2)*64,(timeParam/2)*8+8,64,8,0);}
  }
  if(set == 1){
    if(selParam == 1){if(eventParam == 0){oled.invertedText=1;}}
    oled.drawText(0,1,oled.invertedText,"Type:" + eventTypeName[eventType[matrix]]);
    oled.invertedText=0;
    if(selParam == 1){if(eventParam == 1){oled.invertedText=1;}}
    oled.drawText(8,1,oled.invertedText,"Mode:" + eventModeName[eventMode[matrix]]);
    oled.invertedText=0;
    if(selParam == 1){if(eventParam == 2){oled.invertedText=1;}}
    oled.drawText(0,2,oled.invertedText,"Min:" + String(eventProbMin[matrix]));
    oled.invertedText=0;
    if(selParam == 1){if(eventParam == 3){oled.invertedText=1;}}
    oled.drawText(8,2,oled.invertedText,"Max:" + String(eventProbMax[matrix]));
    oled.invertedText=0;
    if(selParam == 0){oled.drawBox((eventParam%2)*64,(eventParam/2)*8+8,64,8,0);}
  }
}

void ProbSeq::drawInfo(){
  if(set == 0){
    oled.drawText(0,0,1,"Tempo");
    oled.drawText(4,0,0,"Event");
  }
  if(set == 1){
    oled.drawText(0,0,0,"Tempo");
    oled.drawText(4,0,1,"Event");
  }
  for(int i=0;i<4;i++){
    oled.drawText(8,0,0,"Chan:");
    if(i == matrix){oled.invertedText = 1;}
    oled.drawText((i*1)+12,0,oled.invertedText,dectohex(i));
    oled.invertedText = 0;
  }
  // drawDivision();
  drawParams();
}

void ProbSeq::drawMatrix(){
  if(set == 0){
    for(int k=0;k<4;k++){
      if(view == 0){
        for(int i=0;i<4;i++){
          for(int j=0;j<4;j++){
            oled.invertedText = 0;
            if(((i%4)+(j*4))+(division*16) == pos[k]){oled.invertedText = 1;}
            if(timeParam==0){
              oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,boolString(patt[k][(i%4)+(j*4)+(division*16)]));
            }
            if(timeParam==1){
              oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(probs[k][(i%4)+(j*4)+(division*16)]));
            }
            if(timeParam==2){
              oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohexPoint(clockDiv[k][(i%4)+(j*4)+(division*16)]));
            }
            if(timeParam==3){
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
          if(timeParam==0){
            oled.drawText(i,k+4,oled.invertedText,boolString(patt[k][i+(division*16)]));
          }
          if(timeParam==1){
            oled.drawText(i,k+4,oled.invertedText,dectohexPoint(probs[k][i+(division*16)]));
          }
          if(timeParam==2){
            oled.drawText(i,k+4,oled.invertedText,dectohexPoint(clockDiv[k][i+(division*16)]));
          }
          if(timeParam==3){
              if(i + (division*16) == lengthMin[k] && i + (k*4) + (division*16) == lengthMax[k]){
                oled.drawText(i,k+4,oled.invertedText,"A");
              }
              else if(i + (division*16) == lengthMin[k]){oled.drawText(i,k+4,oled.invertedText,"S");}
              else if(i + (division*16) == lengthMax[k]){oled.drawText(i,k+4,oled.invertedText,"E");}
              else{oled.drawText(i,k+4,oled.invertedText,".");}
          }
        }
      }
      if(k==matrix){oled.drawBox(k*32,31,32,33,0);}
    }
  }
  if(set == 1){
    for(int i=0;i<16;i++){
      if(posNote[matrix] == i+(division*16)){oled.invertedText=1;}
      oled.drawText(((i%4)*2)+7,(i/4)+4,oled.invertedText,boolStringInv(activeNote[matrix][i+(division*16)]));
      oled.invertedText=0;
    }
  }
}

void ProbSeq::drawControls(){
  if(b1.held == 1){
      oled.drawText(0,4,0,"Clear 1 2 3 4");  
      oled.drawText(0,5,0,"Fill  1 2 3 4");
  }
  if(b2.held == 1){}
}

void ProbSeq::drawKey(int key){
  if(set==0){
    if(view == 0){
      if(timeParam==0){
        if(patt[matrix][key+(division*16)] == 0){
          kp.set(key,0);
        }
        if(patt[matrix][key+(division*16)] == 1){
          kp.set(key,1);
        }
      }
      if(timeParam==1){
        if(probs[matrix][key+(division*16)] < prob){
          kp.set(key,4);
        }
        if(probs[matrix][key+(division*16)] > prob){
          kp.set(key,2);
        }
        if(probs[matrix][key+(division*16)] == prob){
          kp.set(key,1);
        }
        if(probs[matrix][key+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam==2){
        if(clockDiv[matrix][key+(division*16)] < clockDivision){
          kp.set(key,4);
        }
        if(clockDiv[matrix][key+(division*16)] > clockDivision){
          kp.set(key,2);
        }
        if(clockDiv[matrix][key+(division*16)] == clockDivision){
          kp.set(key,1);
        }
        if(clockDiv[matrix][key+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam==3){
        if(lengthMin[matrix] == key + (division*16)){
          kp.set(lengthMin[matrix]%16,4);
        }
        else if(lengthMax[matrix] == key + (division*16)){
          kp.set(lengthMax[matrix]%16,2);
        }
        else if(key+(division*16) < lengthMax[matrix] && key+(division*16) > lengthMin[matrix]){
          kp.set(key,7);
        }
        else{kp.set(key,0);}
      }
    }
    if(view == 1){
      int i = (key%16)%4;
      int j = (key%16)/4;
      if(timeParam == 0){
        if(patt[j][i+(matrix*4)+(division*16)] == 0){
          kp.set(key,0);
        }
        if(patt[j][i+(matrix*4)+(division*16)] == 1){
          kp.set(key,1);
        }
      }
      if(timeParam == 1){
        if(probs[j][i+(matrix*4)+(division*16)] < prob){
          kp.set(key,4);
        }
        if(probs[j][i+(matrix*4)+(division*16)] > prob){
          kp.set(key,2);
        }
        if(probs[j][i+(matrix*4)+(division*16)] == prob){
          kp.set(key,1);
        }
        if(probs[j][i+(matrix*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam == 2){
        if(clockDiv[j][i+(matrix*4)+(division*16)] < clockDivision){
          kp.set(key,4);
        }
        if(clockDiv[j][i+(matrix*4)+(division*16)] > clockDivision){
          kp.set(key,2);
        }
        if(clockDiv[j][i+(matrix*4)+(division*16)] == clockDivision){
          kp.set(key,1);
        }
        if(clockDiv[j][i+(matrix*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam == 3){
        if(lengthMin[j] == (i%4) + (matrix*4) + (division*16)){
          kp.set(key,4);
        }
        else if(lengthMax[j] == (i%4) + (matrix*4) + (division*16)){
          kp.set(key,2);
        }
        else if((i%4) + (matrix*4) + (division*16) < lengthMax[j] && (i%4) + (matrix*4) + (division*16) > lengthMin[j]){
          kp.set(key,7);
        }
        else{kp.set(key,0);}
      }
    }
  }
}

void ProbSeq::drawMatrixLED(){
  for(int i=0;i<16;i++){drawKey(i);}
  writeNewPosition();
  kp.show();
}

void ProbSeq::drawDivision(){
  // for(int i=0;i<4;i++){
    // if(i == division){oled.invertedText = 1;}
    // oled.drawText((i*1)+8,0,oled.invertedText,dectohex(i));
    // oled.invertedText = 0;
  // }
}

void ProbSeq::followPos(){
  if(follow == 1){
    if(view == 1){matrix = (pos[0]%16)/4;}
    division = (pos[0]%64)/16;
  }
}