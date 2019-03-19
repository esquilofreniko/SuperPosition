ProbSeq::ProbSeq(){
  for(int i=0;i<4;i++){
    for(int j=0;j<16;j++){
      eventProbActive[i][j] = 1;
      eventProbMax[i][j] = eventProbSetMax;
    }
  }
}  

void ProbSeq::run(){
  clock();
  controls();
  if(oled.redraw == 1){drawBg();}
}

void ProbSeq::clock(){
  if(midiclock == 1){
    midiclock = 0;
    updatePosition();
    morph();
    output();
    writeNewPosition();
  }
}

void ProbSeq::updatePosition(){
  //Clear Old Position
  if(set == 0){
    if(view == 0){
      if(pos[channel]/16 == division){
        drawKey(pos[channel]%16);
      }
    }
    else if(view == 1){
      for(int i=0;i<4;i++){
        if(pos[i] < ((channel+1)*4)+(division*16) && pos[i] >= (channel*4)+(division*16)){
          drawKey((pos[i]%4)+(i*4));
        }
      }
    }
  }
  if(set == 1){
    drawKey(posNote[channel]);
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
      if(eventProbActive[p][pos[p]] == 1){
        if(eventStep[p] == 0){
          posNote[p] = pos[p];
        }
      }      
    }
  }
}

void ProbSeq::writeNewPosition(){
  //Write New Position
  if(set == 0){
    if(view == 0){
      if(pos[channel]/16 == division){
        if(patt[channel][pos[channel]] == 0){kp.set(pos[channel]%16,6);}
        if(patt[channel][pos[channel]] == 1){kp.set(pos[channel]%16,3);}
      }
    }
    else if(view == 1){
      for(int i=0;i<4;i++){
        if(pos[i] < ((channel+1)*4)+(division*16) && pos[i] >= (channel*4)+(division*16)){
          if(patt[i][pos[i]] == 0){kp.set((pos[i]%4)+(i*4),6);}
          if(patt[i][pos[i]] == 1){kp.set((pos[i]%4)+(i*4),3);}
        }
      }
    }
  }
  else if(set == 1){
    if(eventMode[channel] == 0){
      kp.set(posNote[channel],6);
    }
  }
  kp.show();
}

void ProbSeq::morph(){
  //Probability Pattern Morph
  if(pattMorph>random(10)){
    for(int i=0;i<4;i++){
      if(clockDivCount[i] == 0){
        if(probs[i][pos[i]] > random(10)){patt[i][pos[i]] = 1;}
        else{patt[i][pos[i]] = 0;}
      }
    }
  }
  for(int i=0;i<4;i++){
    if(eventMode[i] == 0){
      if(eventProbMorph[i] > random(10)){eventProbNote[i][posNote[i]] = random(eventProbMin[i][posNote[i]],eventProbMax[i][posNote[i]]);}
    }
  }
}

void ProbSeq::output(){
  //MIDI Out
  for(int i=0;i<4;i++){
    if(clockDivCount[i]==0){
      if(patt[i][pos[i]] == 1){
        usbMIDI.sendNoteOn(60,60,i+2);
      }
      if(patt[i][pos[i]] == 0){
       usbMIDI.sendNoteOff(60,0,i+2);
      }
    }
    usbMIDI.sendNoteOn(eventProbNote[i][posNote[i]],96,i+6);
  }
}

void ProbSeq::controls(){
  if(kp.pressed == 1){
    if(menu == 0){
      if(b1.held == 0 && b2.held == 0){
        for(int i=0;i<16;i++){
          if(kp.key[i]==1){
            setStep(i);
          }
        }
      }
    }
    else if(menu==1){
      menu = 0;
      selParam = 0;
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
  if(b1.held_t == 1){
    if(menu == 0){
      for(int i=0;i<16;i++){
        if(set == 0){
          if(timeParam==0){patt[channel][i] = 0;}
          if(timeParam==1){probs[channel][i] = 0;}
          if(timeParam==2){clockDiv[channel][i] = 0;}
        }
      }
      drawMatrixLED();
      // for(int i=0;i<4;i++){
      //   if(kp.key[i]==1){
      //     for(int j=lengthMin[i];j<=lengthMax[i];j++){
      //       if(timeParam==0){patt[i][j] = 0;}
      //       if(timeParam==1){probs[i][j] = 0;}
      //       if(timeParam==2){clockDiv[i][j] = 0;}
      //     }
      //     drawMatrixLED();
      //   }
      //   if(kp.key[i+4]==1){
      //     for(int j=lengthMin[i];j<=lengthMax[i];j++){
      //       if(timeParam==0){patt[i][j] = 1;}
      //       if(timeParam==1){probs[i][j] = prob;}
      //       if(timeParam==2){clockDiv[i][j] = clockDivision;}
      //     }
      //     drawMatrixLED();
      //   }  
      // }
    }
  }
  if(b2.held_t == 1){
    if(menu == 0){
      for(int i=0;i<16;i++){
        if(set == 0){
          if(timeParam==0){patt[channel][i] = 1;}
          if(timeParam==1){probs[channel][i] = prob;}
          if(timeParam==2){clockDiv[channel][i] = clockDivision;}
        }
      }
      drawMatrixLED();
    }
  }
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
    if(menu == 0){menu = 1;}
    else{menu = 0;}
    selParam = 0;
    drawMatrixLED();
  }
  if(enc1.rotation != 0){
    channel+= enc1.rotation;
    if(channel>3){
      channel=0;
    }
    if(channel<0){
      channel=3;
    }
    drawMatrixLED();
  }
  if(enc2.rotation != 0){
    if(menu==0){
      if(selParam == 0){
        if(set == 0){
          timeParam += enc2.rotation;
          if(timeParam > 3){timeParam = 0;}
          else if(timeParam < 0){timeParam = 3;}
        }
        else if(set == 1){
          eventParam += enc2.rotation;
          if(eventParam > 3){eventParam = 0;}
          else if(eventParam < 0){eventParam = 3;}
        }
      }
      else if(selParam == 1){
        if(set == 0){
          if(timeParam == 0){
            pattMorph += enc2.rotation;
            if(pattMorph>10){pattMorph=10;}
            else if(pattMorph<0){pattMorph=0;}
          }
          else if(timeParam == 1){
            prob += enc2.rotation;
            if(prob>10){prob = 10;}
            else if(prob<1){prob = 1;}
          }
          else if(timeParam == 2){
            clockDivision += enc2.rotation;
            if(clockDivision > 16){clockDivision=16;}
            else if(clockDivision < 2){clockDivision=2;}
          }
          else if(timeParam == 3){
            if(enc2.rotation == 1){lengthSet = 1;}
            else if(enc2.rotation == -1){lengthSet = 0;}
          }
        }
        else if(set == 1){
          if(eventParam == 0){
            eventProbMorph[channel] += enc2.rotation;
            if(eventProbMorph[channel]<0){eventProbMorph[channel]=0;}
            else if(eventProbMorph[channel]>10){eventProbMorph[channel]=10;}
          }
          else if(eventParam == 1){
            eventProbSetNote += enc2.rotation;
            if(eventProbSetNote<0){eventProbSetNote=0;}
            else if(eventProbSetNote>96){eventProbSetNote=96;}
          }
          else if(eventParam == 2){
            eventProbSetMin += enc2.rotation;
            if(eventProbSetMin<0){eventProbSetMin=0;}
            else if(eventProbSetMin>96){eventProbSetMin=96;}
          }
          else if(eventParam == 3){
            eventProbSetMax += enc2.rotation;
            if(eventProbSetMax<0){eventProbSetMax=0;}
            else if(eventProbSetMax>96){eventProbSetMax=96;}
          }
        }
      }
      drawMatrixLED();
    }
    else if(menu == 1){
      if(selParam == 0){
        if(set == 0){
          timeMenuParam += enc2.rotation;
          if(timeMenuParam > 3){timeMenuParam = 0;}
          if(timeMenuParam < 0){timeMenuParam = 3;}
        }
        if(set == 1){
          eventMenuParam += enc2.rotation;
          if(eventMenuParam > 3){eventMenuParam = 0;}
          if(eventMenuParam < 0){eventMenuParam = 3;}
        }
      }
      else if(selParam == 1){
        if(set == 0){
          if(timeMenuParam == 0){
            view += enc2.rotation;
            if(view < 0){view = 0;}
            else if(view > 1){view = 1;}
          }
        }
        else if(set == 1){
          if(eventMenuParam == 0){
            eventMode[channel] += enc2.rotation;
            if(eventMode[channel]<0){eventMode[channel] = 0;}
            else if(eventMode[channel]>1){eventMode[channel] = 1;}
          }
          else if(eventMenuParam == 1){
            eventStep[channel] += enc2.rotation;
            if(eventStep[channel]<0){eventStep[channel] = 0;}
            else if(eventStep[channel]>1){eventStep[channel] = 1;}
          }
        }
      }
    }
  }
}

void ProbSeq::setStep(int key){
  if(set == 0){
    if(timeParam == 0){
      if(view == 0){
        patt[channel][key + (division*16)] = (patt[channel][key + (division)*16]+1)%2;
      }
      if(view == 1){
        patt[key/4][((key%4)+(channel*4))+(division*16)] = (patt[key/4][((key%4)+(channel*4))+(division*16)]+1)%2;
      }
    }
    if(timeParam == 1){
      if(view == 0){
        if(probs[channel][key + (division)*16] != prob){probs[channel][key + (division)*16] = prob;}
        else{probs[channel][key + (division)*16] = 0;}
      }
      if(view == 1){
        if(probs[key/4][(key%4)+(channel*4) + (division)*16] != prob){probs[key/4][(key%4)+(channel*4) + (division)*16] = prob;}
        else{probs[key/4][(key%4)+(channel*4) + (division)*16] = 0;}
      }
    }
    if(timeParam == 2){
      if(view == 0){
        if(clockDiv[channel][key + (division)*16] != clockDivision){clockDiv[channel][key + (division)*16] = clockDivision;}
        else{clockDiv[channel][key + (division)*16] = 0;}
      }
      if(view == 1){
        if(clockDiv[key/4][(key%4)+(channel*4) + (division)*16] != clockDivision){clockDiv[key/4][(key%4)+(channel*4) + (division)*16] = clockDivision;}
        else{clockDiv[key/4][(key%4)+(channel*4) + (division)*16] = 0;}
      }
    }
    if(timeParam == 3){
      if(view == 0){
        if(lengthSet==0){
          lengthMin[channel] = key + (division*16);
        }
        else if(lengthSet==1){
          lengthMax[channel] = key + (division*16);
        }
        if(lengthMin[channel] > lengthMax[channel]){
          temp = lengthMin[channel];
          lengthMin[channel] = lengthMax[channel];
          lengthMax[channel] = temp;
        }
        drawMatrixLED();
      }
      if(view == 1){
        if(lengthSet==0){
          lengthMin[key/4] = (key%4) + (channel*4) + (division*16);
        }
        else if(lengthSet==1){
          lengthMax[key/4] = (key%4) + (channel*4) + (division*16);
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
  else if(set == 1){
    if(eventParam == 0){
      eventProbActive[channel][key] = (eventProbActive[channel][key]+1)%2;   
    }
    else if(eventParam == 1){
      if(eventProbNote[channel][key] == eventProbSetNote){
        eventProbNote[channel][key] = 0;
      }
      else{
        eventProbNote[channel][key] = eventProbSetNote;
      }
    }
    else if(eventParam == 2){
      if(eventProbMin[channel][key] == eventProbSetMin){
        eventProbMin[channel][key] = 0;  
      }
      else{
        eventProbMin[channel][key] = eventProbSetMin;
      }
    }
    else if(eventParam == 3){
      if(eventProbMax[channel][key] == eventProbSetMax){
        eventProbMax[channel][key] = 0;
      }
      else{
        eventProbMax[channel][key] = eventProbSetMax;
      }
    } 
  }
  drawKey(key);
  kp.show();
}

void ProbSeq::drawBg(){
  oled.clear();
  drawInfo();
  if(menu == 0){
    drawParams();
    drawMatrix();
  }
  else if(menu == 1){
    drawMenu();
  }
}

void ProbSeq::drawParams(){
  if(set == 0){
    if(selParam == 1){if(timeParam == 0){oled.invertedText=1;}}
    oled.drawText(0,1,oled.invertedText,"Morph:" + dectohex(pattMorph));
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
    if(eventParam < 2){
      if(selParam == 1){if(eventParam == 0){oled.invertedText=1;}}
      oled.drawText(0,1,oled.invertedText,"Morph:" + String(eventProbMorph[channel]));
      oled.invertedText=0;
      if(selParam == 1){if(eventParam == 1){oled.invertedText=1;}}
      oled.drawText(8,1,oled.invertedText,"Note:" + String(eventProbSetNote));
      oled.invertedText=0;
    }
    else if(eventParam < 4){
      if(selParam == 1){if(eventParam == 2){oled.invertedText=1;}}
      oled.drawText(0,1,oled.invertedText,"Min:" + String(eventProbSetMin));
      oled.invertedText=0;
      if(selParam == 1){if(eventParam == 3){oled.invertedText=1;}}
      oled.drawText(8,1,oled.invertedText,"Max:" + String(eventProbSetMax));
      oled.invertedText=0;
    }
    else if(eventParam < 6){
      if(selParam == 1){if(eventParam == 4){oled.invertedText=1;}}
      oled.drawText(0,1,oled.invertedText,"Offset:");
      oled.invertedText=0;
      if(selParam == 1){if(eventParam == 5){oled.invertedText=1;}}
      oled.drawText(8,1,oled.invertedText,"Quantize:");
      oled.invertedText=0;
    }
    if(selParam == 0){oled.drawBox((eventParam%2)*64,8,64,8,0);}
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
    if(i == channel){oled.invertedText = 1;}
    oled.drawText((i*1)+12,0,oled.invertedText,dectohex(i));
    oled.invertedText = 0;
  }
}

void ProbSeq::drawMatrix(){
  if(set == 0){
    for(int k=0;k<4;k++){
      if(view == 0){
        for(int i=0;i<4;i++){
          for(int j=0;j<4;j++){
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
            oled.invertedText = 0;
          }
        }
      }
      if(view == 1){
        for(int i=0;i<16;i++){
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
          oled.invertedText = 0;
        }
      }
      if(k==channel){oled.drawBox(k*32,31,32,33,0);}
    }
  }
  if(set == 1){
    for(int i=0;i<16;i++){
      if(posNote[channel] == i+(division*16)){oled.invertedText=1;}
      if(eventParam == 0){
        oled.drawText(((i%4)*2)+8,(i/4)+4,oled.invertedText,boolString(eventProbActive[channel][i]));
      }
      else if(eventParam == 1){
        oled.drawText(((i%4)*2)+8,(i/4)+4,oled.invertedText,String(eventProbNote[channel][i]));
      }
      else if(eventParam == 2){
        oled.drawText(((i%4)*2)+8,(i/4)+4,oled.invertedText,String(eventProbMin[channel][i]));
      }
      else if(eventParam == 3){
        oled.drawText(((i%4)*2)+8,(i/4)+4,oled.invertedText,String(eventProbMax[channel][i]));
      }
      oled.invertedText = 0;
    }
  }
}

void ProbSeq::drawKey(int key){
  if(set==0){
    if(view == 0){
      if(timeParam==0){
        if(patt[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
        if(patt[channel][key+(division*16)] == 1){
          kp.set(key,1);
        }
      }
      if(timeParam==1){
        if(probs[channel][key+(division*16)] < prob){
          kp.set(key,4);
        }
        if(probs[channel][key+(division*16)] > prob){
          kp.set(key,2);
        }
        if(probs[channel][key+(division*16)] == prob){
          kp.set(key,1);
        }
        if(probs[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam==2){
        if(clockDiv[channel][key+(division*16)] < clockDivision){
          kp.set(key,4);
        }
        if(clockDiv[channel][key+(division*16)] > clockDivision){
          kp.set(key,2);
        }
        if(clockDiv[channel][key+(division*16)] == clockDivision){
          kp.set(key,1);
        }
        if(clockDiv[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam==3){
        if(lengthMin[channel] == key + (division*16)){
          kp.set(lengthMin[channel]%16,4);
        }
        else if(lengthMax[channel] == key + (division*16)){
          kp.set(lengthMax[channel]%16,2);
        }
        else if(key+(division*16) < lengthMax[channel] && key+(division*16) > lengthMin[channel]){
          kp.set(key,7);
        }
        else{kp.set(key,0);}
      }
    }
    if(view == 1){
      int i = (key%16)%4;
      int j = (key%16)/4;
      if(timeParam == 0){
        if(patt[j][i+(channel*4)+(division*16)] == 0){
          kp.set(key,0);
        }
        if(patt[j][i+(channel*4)+(division*16)] == 1){
          kp.set(key,1);
        }
      }
      if(timeParam == 1){
        if(probs[j][i+(channel*4)+(division*16)] < prob){
          kp.set(key,4);
        }
        if(probs[j][i+(channel*4)+(division*16)] > prob){
          kp.set(key,2);
        }
        if(probs[j][i+(channel*4)+(division*16)] == prob){
          kp.set(key,1);
        }
        if(probs[j][i+(channel*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam == 2){
        if(clockDiv[j][i+(channel*4)+(division*16)] < clockDivision){
          kp.set(key,4);
        }
        if(clockDiv[j][i+(channel*4)+(division*16)] > clockDivision){
          kp.set(key,2);
        }
        if(clockDiv[j][i+(channel*4)+(division*16)] == clockDivision){
          kp.set(key,1);
        }
        if(clockDiv[j][i+(channel*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(timeParam == 3){
        if(lengthMin[j] == (i%4) + (channel*4) + (division*16)){
          kp.set(key,4);
        }
        else if(lengthMax[j] == (i%4) + (channel*4) + (division*16)){
          kp.set(key,2);
        }
        else if((i%4) + (channel*4) + (division*16) < lengthMax[j] && (i%4) + (channel*4) + (division*16) > lengthMin[j]){
          kp.set(key,7);
        }
        else{kp.set(key,0);}
      }
    }
  }
  if(set == 1){
      if(eventParam==0){
        if(eventProbActive[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
        if(eventProbActive[channel][key+(division*16)] == 1){
          kp.set(key,1);
        }
      }
      if(eventParam==1){
        if(eventProbNote[channel][key+(division*16)] < eventProbSetNote){
          kp.set(key,4);
        }
        if(eventProbNote[channel][key+(division*16)] > eventProbSetNote){
          kp.set(key,2);
        }
        if(eventProbNote[channel][key+(division*16)] == eventProbSetNote){
          kp.set(key,1);
        }
        if(eventProbNote[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(eventParam==2){
        if(eventProbMin[channel][key+(division*16)] < eventProbSetMin){
          kp.set(key,4);
        }
        if(eventProbMin[channel][key+(division*16)] > eventProbSetMin){
          kp.set(key,2);
        }
        if(eventProbMin[channel][key+(division*16)] == eventProbSetMin){
          kp.set(key,1);
        }
        if(eventProbMin[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      if(eventParam==3){
        if(eventProbMax[channel][key+(division*16)] < eventProbSetMax){
          kp.set(key,4);
        }
        if(eventProbMax[channel][key+(division*16)] > eventProbSetMax){
          kp.set(key,2);
        }
        if(eventProbMax[channel][key+(division*16)] == eventProbSetMax){
          kp.set(key,1);
        }
        if(eventProbMax[channel][key+(division*16)] == 0){
          kp.set(key,0);
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

void ProbSeq::drawMenu(){
  if(set == 0){
    if(selParam == 1){if(timeMenuParam == 0){oled.invertedText=1;}}
    if(view == 0){oled.drawText(0,1,oled.invertedText,"(G)View:Vertical");}
    else if(view == 1){oled.drawText(0,1,oled.invertedText,"(G)View:Horizontal");}
    oled.invertedText = 0;
    if(selParam == 0){oled.drawBox(0,(timeMenuParam+1)*8,128,8,0);}
  }
  else if(set == 1){
    if(selParam == 1){if(eventMenuParam == 0){oled.invertedText=1;}}
    oled.drawText(0,1,oled.invertedText,"Mode:" + eventModeName[eventMode[channel]]);
    oled.invertedText = 0;
    if(selParam == 1){if(eventMenuParam == 1){oled.invertedText=1;}}
    oled.drawText(0,2,oled.invertedText,"Step:" + eventStepName[eventStep[channel]]);
    oled.invertedText = 0;
    if(selParam == 0){oled.drawBox(0,(eventMenuParam+1)*8,128,8,0);}
  }
}