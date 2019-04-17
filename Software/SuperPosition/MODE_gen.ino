Gen::Gen(){
  for(int i=0;i<4;i++){
    for(int j=0;j<96;j++){
      if(j<64){
        eventProbActive[i][j] = 1;
        eventProbMax[i][j] = eventProbSetMax;
        burstProb[i][j] = 10;
      }
      eventQuant[i][j] = 1;
    }
  }
}  

void Gen::run(){
  if(adc.trig[1] == 1){reset();}
  clock();
  ratcheting();
  controls();
  if(oled.redraw == 1){drawBg();}
  if(adc.trig[0] == 1 || millis() - lastTrig > 1000){
    if(drawLEDS == 1){drawMatrixLED();drawLEDS=0;}
  }
  if(showLEDS == 1){kp.show();showLEDS = 0;}
}

void Gen::ratcheting(){
  for(int i=0;i<4;i++){
    if(ratchetTrig[i] > 0 && patt[i][pos[i]]==1){
      if(millis() - ratchetCounter[i] > (clockSpeed / ratchet[i])){
        gate.write(i,1);
        ratchetCounter[i] = millis();
        ratchetTrig[i] -= 1;
      }
    }
  }
}

void Gen::reset(){
  for(int i=0;i<4;i++){
    if(channel == i){drawKey(pos[i]);showLEDS = 1;}
    pos[i] = lengthMin[i];
    posNote[i] = eventSizeMin[i];
    for(int count=0;count<16;count++){
      if(eventProbActive[i][posNote[i]] == 0){
        posNote[i] += 1;
        if(posNote[i] > eventSizeMax[i]){posNote[i] = eventSizeMin[i];}
      }
    }
    clockDivCount[i] = 0;
    eventDivCount[i] = 0;
  }
  morphNote();
  morphPatt();
  output();
  writeNewPosition();
}

void Gen::clock(){
  if(adc.trig[0] == 1){
    clockSpeed = millis() - lastTrig;
    lastTrig = millis();
    updatePosition();
    morphNote();
    morphPatt();
    output();
    writeNewPosition();
  }
}

void Gen::updatePosition(){
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
    if(posNote[channel]/16 == division){
      drawKey(posNote[channel]%16);
    }
  }
  for(int i=0;i<4;i++){
    //Update Time Position
    clockDivOp = clockDiv[i][pos[i]];
    if(clockDivOp==0){clockDivOp=1;}
    clockDivCount[i] += 1;
    clockDivCount[i] %= clockDivOp;
    if(clockDivCount[i]==0){
      pos[i] += 1;
      if(pos[i] > lengthMax[i]){pos[i] = lengthMin[i];}      
    }
    //Update Event Position
    if(eventStep[i] == 0){
      if(eventProbActive[i][pos[i]]==1){posNote[i] = pos[i];}
    }
    else if(eventStep[i] == 1){
      clockDivOp = eventDiv[i][posNote[i]];
      if(clockDivOp==0){clockDivOp=1;}
      eventDivCount[i] += 1;
      eventDivCount[i] %= clockDivOp;
      if(eventDivCount[i]==0){
        posNote[i] += 1;
        if(posNote[i] > eventSizeMax[i]){posNote[i] = eventSizeMin[i];}
        if(eventSkip[i] == 0){
          //Skip Unactive
          for(int count=0;count<16;count++){
            if(eventProbActive[i][posNote[i]] == 0){
              posNote[i] += 1;
              if(posNote[i] > eventSizeMax[i]){posNote[i] = eventSizeMin[i];}
            }
            else{break;}
          }
        }
      } 
    }
  }
}

void Gen::writeNewPosition(){
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
    if(posNote[channel]/16 == division){
      kp.set(posNote[channel]%16,6);
    }
  }
  showLEDS = 1;
}

void Gen::morphPatt(){
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
    if(clockDivCount[i] == 0){
      if(burstProb[i][pos[i]]>random(10)){ratchet[i] = burst[i][pos[i]];ratchetTrig[i] = burst[i][pos[i]]-1;}
      else{ratchet[i] = 0;}
    }
  }
}

void Gen::morphNote(){
  //Morph Event
  for(int i=0;i<4;i++){
    if(posNoteOld[i] != posNote[i]){
      posNoteOld[i] = posNote[i];
      if(eventMode[i] == 0){
        if(eventMorph[i] > random(10)){
          eventNote[i][posNote[i]] = random(eventProbMin[i][posNote[i]],eventProbMax[i][posNote[i]]);
          //Quantize
          for(int quantize=0;quantize<96;quantize++){
            int tMin = eventNote[i][posNote[i]] - quantize;
            if(tMin >= 0){
              if(eventQuant[i][tMin] == 1){
                eventNote[i][posNote[i]] = tMin;
                break;
              }
            }
          }
        }
      }
    }
  }
}

void Gen::output(){
  //Out
  for(int i=3;i>-1;i--){
    dac.write(i,noteToVolt(eventNote[i][posNote[i]]));
    if(clockDivCount[i]==0){
      // gate.write(i,patt[i][pos[i]]);
      if(patt[i][pos[i]]==1){
        for(int j=0;j<4;j++){
          if(gateOut[i][j] == 1){
            gate.write(j,1);
            ratchetCounter[i] = millis();
          }
        }
      }
    }
  }
}

void Gen::controls(){
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
    drawLEDS = 1;
  }
  if(b2.clicked== 1){
    division++;
    division%=4;
    drawLEDS = 1;
  }
  if(b1.held_t == 1){
    if(menu == 0){
      for(int i=0;i<16;i++){
        if(set == 0){
          if(timeParam==0){patt[channel][i] = 0;}
          else if(timeParam==1){probs[channel][i] = 0;}
          else if(timeParam==2){burst[channel][i] = 0;}
          else if(timeParam==3){burstProb[channel][i] = 0;}
          else if(timeParam==4){clockDiv[channel][i] = 0;}
        }
        else if(set == 1){
          if(eventParam==0){eventProbActive[channel][i]=0;}
          else if(eventParam==1){eventNote[channel][i]=0;}
          else if(eventParam==2){eventProbMin[channel][i]=0;}
          else if(eventParam==3){eventProbMax[channel][i]=0;}
          else if(eventParam==4){eventSlew[channel][i] = 0;}
          else if(eventParam==5){
            if(eventQuantMode[channel] == 0){
              for(int j=0;j<6;j++){
                int j2 = j*16;
                eventQuant[channel][i+j2]=0;
              }
            }
            else{eventQuant[channel][i+((eventQuantMode[channel]-1)*16)]=0;}
          }
          else if(eventParam==6){eventDiv[channel][i] = 0;}
        }
      }
      drawLEDS = 1;
    }
  }
  if(b2.held_t == 1){
    if(menu == 0){
      for(int i=0;i<16;i++){
        if(set == 0){
          if(timeParam==0){patt[channel][i] = 1;}
          else if(timeParam==1){probs[channel][i] = prob;}
          else if(timeParam==2){burst[channel][i] = setBurst;}
          else if(timeParam==3){burstProb[channel][i] = setBurstProb;}
          else if(timeParam==4){clockDiv[channel][i] = clockDivision;}
        }
        else if(set == 1){
          if(eventParam==0){eventProbActive[channel][i]=1;}
          else if(eventParam==1){eventNote[channel][i]=eventProbSetNote;}
          else if(eventParam==2){eventProbMin[channel][i]=eventProbSetMin;}
          else if(eventParam==3){eventProbMax[channel][i]=eventProbSetMax;}
          else if(eventParam==4){eventSlew[channel][i] = eventSetSlew;}
          else if(eventParam==5){
            if(eventQuantMode[channel] == 0){
              for(int j=0;j<6;j++){
                int j2 = j*16;
                eventQuant[channel][i+j2]=1;
              }
            }
            else{eventQuant[channel][i+((eventQuantMode[channel]-1)*16)]=1;}
          }
          else if(eventParam==6){eventDiv[channel][i] = eventDivision;}
        }
      }
      drawLEDS = 1;
    }
  }
  if(enc1.clicked == 1){
    for(int i=0;i<4;i++){
      if(channel == i){drawKey(pos[i]);showLEDS = 1;}
      pos[i] = lengthMin[i]-1;
      posNote[i] = -1;
      clockDivCount[i] = -1;
      eventDivCount[i] = -1;
    }
  }
  if(enc2.clicked == 1){
    selParam = (selParam + 1)%2;
  }
  if(enc2.held_t==1){
    menu = !menu;
    selParam = 0;
    drawLEDS = 1;
  }
  if(enc1.rotation != 0){
    drawLEDS = 1;
    channel+= enc1.rotation;
    if(channel>3){channel=0;}
    if(channel<0){channel=3;}
  }
  if(enc2.rotation != 0){
    if(eventStep[channel]==0){eventParamMax = 5;}
    else{eventParamMax = 7;}
    if(menu==0){
      drawLEDS = 1;
      if(selParam == 0){
        if(set == 0){
          timeParam += enc2.rotation;
          if(timeParam > timeParamMax){timeParam = 0;}
          else if(timeParam < 0){timeParam = timeParamMax;}
        }
        else if(set == 1){
          eventParam += enc2.rotation;
          if(eventParam > eventParamMax){eventParam = 0;}
          else if(eventParam < 0){eventParam = eventParamMax;}
        }
      }
      else if(selParam == 1){
        if(set == 0){
          if(timeParam == 0){
            pattMorph += enc2.rotation;
            pattMorph = limit(pattMorph,0,10);
          }
          else if(timeParam == 1){
            prob += enc2.rotation;
            prob = limit(prob,1,10);
          }
          else if(timeParam == 2){
            setBurst += enc2.rotation;
            setBurst = limit(setBurst,2,8);
          }
          else if(timeParam == 3){
            setBurstProb += enc2.rotation;
            setBurstProb = limit(setBurstProb,1,10);
          }
          else if(timeParam == 4){
            clockDivision += enc2.rotation;
            clockDivision = limit(clockDivision,2,16);
          }
          else if(timeParam == 5){
            if(enc2.rotation == 1){lengthSet = 1;}
            else if(enc2.rotation == -1){lengthSet = 0;}
          }
        }
        else if(set == 1){
          if(eventParam == 0){
            eventMorph[channel] += enc2.rotation;
            eventMorph[channel] = limit(eventMorph[channel],0,10);
          }
          else if(eventParam == 1){
            eventProbSetNote += enc2.rotation;
            eventProbSetNote = limit(eventProbSetNote,0,96);
          }
          else if(eventParam == 2){
            eventProbSetMin += enc2.rotation;
            eventProbSetMin = limit(eventProbSetMin,0,96);
          }
          else if(eventParam == 3){
            eventProbSetMax += enc2.rotation;
            eventProbSetMax = limit(eventProbSetMax,0,96);
          }
          else if(eventParam == 4){
            eventSetSlew += enc2.rotation;
            eventSetSlew = limit(eventSetSlew,0,16);
          }
          else if(eventParam == 5){
            eventQuantMode[channel] += enc2.rotation;
            eventQuantMode[channel] = limit(eventQuantMode[channel],0,6);
          }
          else if(eventParam == 6){
            eventDivision += enc2.rotation;
            eventDivision = limit(eventDivision,2,16);
          }
          else if(eventParam == 7){
            if(enc2.rotation == 1){eventSizeSet = 1;}
            else if(enc2.rotation == -1){eventSizeSet = 0;}
          }
        }
      }
    }
    else if(menu == 1){
      if(selParam == 0){
        if(set == 0){
          timeMenuParam += enc2.rotation;
          timeMenuParam = limit(timeMenuParam,0,3);
        }
        if(set == 1){
          eventMenuParam += enc2.rotation;
          eventMenuParam = limit(eventMenuParam,0,3);
        }
      }
      else if(selParam == 1){
        if(set == 0){
          if(timeMenuParam == 0){
            view += enc2.rotation;
            view = limit(view,0,1);
          }
        }
        else if(set == 1){
          if(eventMenuParam == 0){
            eventMode[channel] += enc2.rotation;
            eventMode[channel] = limit(eventMode[channel],0,1);
          }
          else if(eventMenuParam == 1){
            eventStep[channel] += enc2.rotation;
            eventStep[channel] = limit(eventStep[channel],0,2);
            if(eventStep[channel]==0){eventParamMax = 5;}
            else{eventParamMax = 7;}
            if(eventParam > eventParamMax){eventParam = 0;}
            drawLEDS = 1;
          }
          else if(eventMenuParam == 2){
            eventSkip[channel] += enc2.rotation;
            eventSkip[channel] = limit(eventSkip[channel],0,1);
          }
        }
      }
    }
  }
}

void Gen::setStep(int key){
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
    else if(timeParam == 2){
      if(view == 0){
        if(burst[channel][key + (division)*16] != setBurst){burst[channel][key + (division)*16] = setBurst;}
        else{burst[channel][key + (division)*16] = 0;}
      }
      if(view == 1){
        if(burst[key/4][(key%4)+(channel*4) + (division)*16] != setBurst){burst[key/4][(key%4)+(channel*4) + (division)*16] = setBurst;}
        else{burst[key/4][(key%4)+(channel*4) + (division)*16] = 0;}
      }
    }
    else if(timeParam == 3){
      if(view == 0){
        if(burstProb[channel][key + (division)*16] != setBurstProb){burstProb[channel][key + (division)*16] = setBurstProb;}
        else{burstProb[channel][key + (division)*16] = 0;}
      }
      if(view == 1){
        if(burstProb[key/4][(key%4)+(channel*4) + (division)*16] != setBurstProb){burstProb[key/4][(key%4)+(channel*4) + (division)*16] = setBurstProb;}
        else{burstProb[key/4][(key%4)+(channel*4) + (division)*16] = 0;}
      }
    }
    if(timeParam == 4){
      if(view == 0){
        if(clockDiv[channel][key + (division)*16] != clockDivision){clockDiv[channel][key + (division)*16] = clockDivision;}
        else{clockDiv[channel][key + (division)*16] = 0;}
      }
      if(view == 1){
        if(clockDiv[key/4][(key%4)+(channel*4) + (division)*16] != clockDivision){clockDiv[key/4][(key%4)+(channel*4) + (division)*16] = clockDivision;}
        else{clockDiv[key/4][(key%4)+(channel*4) + (division)*16] = 0;}
      }
    }
    if(timeParam == 5){
      if(view == 0){
        if(lengthSet==0){
          lengthMin[channel] = key + (division*16);
        }
        else if(lengthSet==1){
          lengthMax[channel] = key + (division*16);
        }
        if(lengthMin[channel] > lengthMax[channel]){
          int t = lengthMin[channel];
          lengthMin[channel] = lengthMax[channel];
          lengthMax[channel] = t;
        }
        drawLEDS = 1;
      }
      if(view == 1){
        if(lengthSet==0){
          lengthMin[key/4] = (key%4) + (channel*4) + (division*16);
        }
        else if(lengthSet==1){
          lengthMax[key/4] = (key%4) + (channel*4) + (division*16);
        }
        if(lengthMin[key/4] > lengthMax[key/4]){
          int t = lengthMin[key/4];
          lengthMin[key/4] = lengthMax[key/4];
          lengthMax[key/4] = t;
        }
        drawLEDS = 1;
      }
    }
  }
  else if(set == 1){
    if(eventParam == 0){
      eventProbActive[channel][key+(division*16)] = (eventProbActive[channel][key+(division*16)]+1)%2;   
    }
    else if(eventParam == 1){
      if(eventNote[channel][key+(division*16)] == eventProbSetNote){
        eventNote[channel][key+(division*16)] = 0;
      }
      else{
        eventNote[channel][key+(division*16)] = eventProbSetNote;
      }
    }
    else if(eventParam == 2){
      if(eventProbMin[channel][key+(division*16)] == eventProbSetMin){
        eventProbMin[channel][key+(division*16)] = 0;  
      }
      else{
        eventProbMin[channel][key+(division*16)] = eventProbSetMin;
      }
    }
    else if(eventParam == 3){
      if(eventProbMax[channel][key+(division*16)] == eventProbSetMax){
        eventProbMax[channel][key+(division*16)] = 0;
      }
      else{
        eventProbMax[channel][key+(division*16)] = eventProbSetMax;
      }
    }
    else if(eventParam == 4){
      if(eventSlew[channel][key+(division*16)] == eventSetSlew){eventSlew[channel][key+(division*16)] = 0;}
      else{eventSlew[channel][key+(division*16)] = eventSetSlew;}
    } 
    else if(eventParam == 5){
      int revKey = ((3-(key/4))*4)+(key%4);
      if(eventQuantMode[channel] == 0){
        if(revKey < 12){
          eventQuant[channel][revKey] = !eventQuant[channel][revKey];
          for(int i=0;i<9;i++){
            int octave = i * 12;
            eventQuant[channel][revKey + octave] = eventQuant[channel][revKey];
          }
        }
      }
      else{
        int t = (eventQuantMode[channel]-1) * 16;
        eventQuant[channel][revKey+t] = !eventQuant[channel][revKey+t];
      }
    }
    else if(eventParam == 6){
      if(eventDiv[channel][key+(division*16)] == eventDivision){eventDiv[channel][key+(division*16)] = 0;}
      else{eventDiv[channel][key+(division*16)] = eventDivision;}
    } 
    else if(eventParam == 7){
        if(eventSizeSet==0){
          eventSizeMin[channel] = key + (division*16);
        }
        else if(eventSizeSet==1){
          eventSizeMax[channel] = key + (division*16);
        }
        if(eventSizeMin[channel] > eventSizeMax[channel]){
          int t = eventSizeMin[channel];
          eventSizeMin[channel] = eventSizeMax[channel];
          eventSizeMax[channel] = t;
        }
        drawLEDS = 1;
    }
  }
  drawKey(key);
  showLEDS = 1;
}

void Gen::drawBg(){
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

void Gen::drawParams(){
  if(set == 0){
    if(timeParam < 2){
      if(selParam == 1){if(timeParam == 0){oled.invertedText=1;}}
      oled.drawText(0,2,oled.invertedText,"Morph:" + dectohex(pattMorph));
      oled.invertedText=0;
      if(selParam == 1){if(timeParam == 1){oled.invertedText=1;}}
      oled.drawText(8,2,oled.invertedText,"Prob:" + dectohex(prob));
      oled.invertedText=0;
    }
    else if(timeParam < 4){
      if(selParam == 1){if(timeParam == 2){oled.invertedText=1;}}
      oled.drawText(0,2,oled.invertedText,"Burst:" + dectohex(setBurst));
      oled.invertedText=0;
      if(selParam == 1){if(timeParam == 3){oled.invertedText=1;}}
      oled.drawText(8,2,oled.invertedText,"BProb:" + dectohex(setBurstProb));
      oled.invertedText=0;  
    }
    else if(timeParam < 6){
      if(selParam == 1){if(timeParam == 4){oled.invertedText=1;}}
      oled.drawText(0,2,oled.invertedText,"Div:" + dectohex(clockDivision));
      oled.invertedText=0;
      if(selParam == 1){if(timeParam==5){oled.invertedText=1;}}
      if(lengthSet == 0){oled.drawText(8,2,oled.invertedText,"Size:Start");}
      if(lengthSet == 1){oled.drawText(8,2,oled.invertedText,"Size:End");}
      oled.invertedText=0;  
    }
    if(selParam == 0){oled.drawBox((timeParam%2)*64,15,64,10,0);}
  }
  if(set == 1){
    if (eventParam < 2){
      if(selParam == 1){if(eventParam == 0){oled.invertedText=1;}}
      oled.drawText(0,2,oled.invertedText,"Morph:" + String(eventMorph[channel]));
      oled.invertedText=0;
      if(selParam == 1){if(eventParam == 1){oled.invertedText=1;}}
      oled.drawText(8,2,oled.invertedText,"Note:" + String(eventProbSetNote));
      oled.invertedText=0;
    }
    else if (eventParam < 4){
      if(selParam == 1){if(eventParam == 2){oled.invertedText=1;}}
      oled.drawText(0,2,oled.invertedText,"Min:" + String(eventProbSetMin));
      oled.invertedText=0;
      if(selParam == 1){if(eventParam == 3){oled.invertedText=1;}}
      oled.drawText(8,2,oled.invertedText,"Max:" + String(eventProbSetMax));
      oled.invertedText=0;
    }
    else if (eventParam < 6){
      if(selParam == 1){if(eventParam == 4){oled.invertedText=1;}}
      oled.drawText(0,2,oled.invertedText,"Slew:"+String(eventSetSlew));
      oled.invertedText=0;
      if(selParam == 1){if(eventParam == 5){oled.invertedText=1;}}
      if(eventQuantMode[channel]==0){oled.drawText(8,2,oled.invertedText,"Quant:Scl");}
      else{oled.drawText(8,2,oled.invertedText,"Quant:+"+String((eventQuantMode[channel]-1)*16));}
      oled.invertedText=0;
    }
    else if (eventParam < 8){
      if(selParam == 1){if(eventParam == 6){oled.invertedText=1;}}
      oled.drawText(0,2,oled.invertedText,"Div:"+String(eventDivision));
      oled.invertedText=0;
      if(selParam == 1){if(eventParam==7){oled.invertedText=1;}}
      if(eventSizeSet == 0){oled.drawText(8,2,oled.invertedText,"Size:Start");}
      if(eventSizeSet == 1){oled.drawText(8,2,oled.invertedText,"Size:End");}
      oled.invertedText=0;  
    }
    if(selParam == 0){oled.drawBox((eventParam%2)*64,15,64,10,0);}
  }
}

void Gen::drawInfo(){
  if(set == 0){
    oled.drawText(0,0,1,"Tempo");
    oled.drawText(4,0,0,"Event");
  }
  if(set == 1){
    oled.drawText(0,0,0,"Tempo");
    oled.drawText(4,0,1,"Event");
  }
  for(int i=0;i<4;i++){
    if(i == division){oled.invertedText = 1;}
    oled.drawText((i*1)+8,0,oled.invertedText,dectohex(i));
    oled.invertedText = 0;
  }
  for(int i=0;i<4;i++){
    if(i == channel){oled.invertedText = 1;}
    oled.drawText((i*1)+12,0,oled.invertedText,dectohex(i));
    oled.invertedText = 0;
  }
}

void Gen::drawMatrix(){
  if(set == 0){
    for(int k=0;k<4;k++){
      if(view == 0){
        for(int i=0;i<16;i++){
          if(i+(division*16) == pos[k]){oled.invertedText = 1;}
          if(timeParam==0){
            oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,boolString(patt[k][i+(division*16)]));
          }
          else if(timeParam==1){
            oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,probString(probs[k][i+(division*16)]));
          }
          else if(timeParam == 2){
            oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,dectohexPoint(burst[k][i+(division*16)]));
          }
          else if(timeParam == 3){
            oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,probString(burstProb[k][i+(division*16)]));
          }
          else if(timeParam==4){
            oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,dectohexPoint(clockDiv[k][i+(division*16)]));
          }
          else if(timeParam==5){
            if(i+(division*16) == lengthMin[k] && i+(division*16) == lengthMax[k]){
              oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,"A");
            }
            else if(i+(division*16) == lengthMin[k]){oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,"S");}
            else if(i+(division*16) == lengthMax[k]){oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,"E");}
            else{oled.drawText((i%4)+(k*4),(i/4)+4,oled.invertedText,".");}
          }
          oled.invertedText = 0;
        }
      }
      if(view == 1){
        for(int i=0;i<16;i++){
          if(pos[k] == i+(division*16)){oled.invertedText = 1;}
          if(timeParam==0){
            oled.drawText(i,k+4,oled.invertedText,boolString(patt[k][i+(division*16)]));
          }
          else if(timeParam==1){
            oled.drawText(i,k+4,oled.invertedText,probString(probs[k][i+(division*16)]));
          }
          else if(timeParam==2){
            oled.drawText(i,k+4,oled.invertedText,dectohexPoint(burst[k][i+(division*16)]));
          }
          else if(timeParam==3){
            oled.drawText(i,k+4,oled.invertedText,probString(burstProb[k][i+(division*16)]));
          }
          else if(timeParam==4){
            oled.drawText(i,k+4,oled.invertedText,dectohexPoint(clockDiv[k][i+(division*16)]));
          }
          else if(timeParam==5){
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
      if(eventParam < 2){
        oled.drawText(((i%4)*2)+0,(i/4)+4,oled.invertedText,boolString(eventProbActive[channel][i+(division*16)]));
        oled.drawText(((i%4)*2)+8,(i/4)+4,oled.invertedText,zeroPoint(eventNote[channel][i+(division*16)]));
      }
      else if(eventParam < 4){
        oled.drawText(((i%4)*2)+0,(i/4)+4,oled.invertedText,zeroPoint(eventProbMin[channel][i+(division*16)]));
        oled.drawText(((i%4)*2)+8,(i/4)+4,oled.invertedText,zeroPoint(eventProbMax[channel][i+(division*16)]));  
      }
      else if(eventParam < 6){
        oled.drawText(((i%4)*2)+0,(i/4)+4,oled.invertedText,zeroPoint(eventSlew[channel][i+(division*16)]));
        oled.invertedText = 0;
        if(eventQuantMode[channel] == 0){
          if(i<12){
            int t = (eventQuantMode[channel]) * 16;
            if(eventQuant[channel][i+t] == 1){oled.invertedText = 1;}
            oled.drawText(((i%4)*2)+8,7-(i/4),oled.invertedText,String(i+t));
          }
        }
        else{
          int t = (eventQuantMode[channel]-1) * 16;
          if(eventQuant[channel][i+t] == 1){oled.invertedText = 1;}
          oled.drawText(((i%4)*2)+8,7-(i/4),oled.invertedText,String(i+t));
        }

      }
      else if(eventParam < 8){
        oled.drawText(((i%4)*2)+0,(i/4)+4,oled.invertedText,zeroPoint(eventDiv[channel][i+(division*16)]));    
        if(i+(division*16) == eventSizeMin[channel] && i+(division*16) == eventSizeMax[channel]){
          oled.drawText((i%4)*2+8,(i/4)+4,oled.invertedText,"A");
        }
        else if(i+(division*16) == eventSizeMin[channel]){oled.drawText((i%4)*2+8,(i/4)+4,oled.invertedText,"S");}
        else if(i+(division*16) == eventSizeMax[channel]){oled.drawText((i%4)*2+8,(i/4)+4,oled.invertedText,"E");}
        else{oled.drawText((i%4)*2+8,(i/4)+4,oled.invertedText,".");}
      }
      oled.invertedText = 0;
    }
  }
}

void Gen::drawKey(int key){
  if(set==0){
    if(view == 0){
      if(timeParam==0){
        if(patt[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
        else if(patt[channel][key+(division*16)] == 1){
          kp.set(key,1);
        }
      }
      else if(timeParam==1){
        if(probs[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
        else if(probs[channel][key+(division*16)] < prob){
          kp.set(key,4);
        }
        else if(probs[channel][key+(division*16)] > prob){
          kp.set(key,2);
        }
        else if(probs[channel][key+(division*16)] == prob){
          kp.set(key,1);
        }
      }
      else if(timeParam==2){
        if(burst[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
        else if(burst[channel][key+(division*16)] < setBurst){
          kp.set(key,4);
        }
        else if(burst[channel][key+(division*16)] > setBurst){
          kp.set(key,2);
        }
        else if(burst[channel][key+(division*16)] == setBurst){
          kp.set(key,1);
        }
      }
      else if(timeParam==3){
        if(burstProb[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
        else if(burstProb[channel][key+(division*16)] < setBurstProb){
          kp.set(key,4);
        }
        else if(burstProb[channel][key+(division*16)] > setBurstProb){
          kp.set(key,2);
        }
        else if(burstProb[channel][key+(division*16)] == setBurstProb){
          kp.set(key,1);
        }
      }
      else if(timeParam==4){
        if(clockDiv[channel][key+(division*16)] == 0){
          kp.set(key,0);
        }
        else if(clockDiv[channel][key+(division*16)] < clockDivision){
          kp.set(key,4);
        }
        else if(clockDiv[channel][key+(division*16)] > clockDivision){
          kp.set(key,2);
        }
        else if(clockDiv[channel][key+(division*16)] == clockDivision){
          kp.set(key,1);
        }
      }
      if(timeParam==5){
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
        else if(patt[j][i+(channel*4)+(division*16)] == 1){
          kp.set(key,1);
        }
      }
      else if(timeParam == 1){
        if(probs[j][i+(channel*4)+(division*16)] < prob){
          kp.set(key,4);
        }
        else if(probs[j][i+(channel*4)+(division*16)] > prob){
          kp.set(key,2);
        }
        else if(probs[j][i+(channel*4)+(division*16)] == prob){
          kp.set(key,1);
        }
        else if(probs[j][i+(channel*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      else if(timeParam == 2){
        if(burst[j][i+(channel*4)+(division*16)] < setBurst){
          kp.set(key,4);
        }
        else if(burst[j][i+(channel*4)+(division*16)] > setBurst){
          kp.set(key,2);
        }
        else if(burst[j][i+(channel*4)+(division*16)] == setBurst){
          kp.set(key,1);
        }
        else if(burst[j][i+(channel*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      else if(timeParam == 3){
        if(burstProb[j][i+(channel*4)+(division*16)] < setBurstProb){
          kp.set(key,4);
        }
        else if(burstProb[j][i+(channel*4)+(division*16)] > setBurstProb){
          kp.set(key,2);
        }
        else if(burstProb[j][i+(channel*4)+(division*16)] == setBurstProb){
          kp.set(key,1);
        }
        else if(burstProb[j][i+(channel*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      else if(timeParam == 4){
        if(clockDiv[j][i+(channel*4)+(division*16)] < clockDivision){
          kp.set(key,4);
        }
        else if(clockDiv[j][i+(channel*4)+(division*16)] > clockDivision){
          kp.set(key,2);
        }
        else if(clockDiv[j][i+(channel*4)+(division*16)] == clockDivision){
          kp.set(key,1);
        }
        else if(clockDiv[j][i+(channel*4)+(division*16)] == 0){
          kp.set(key,0);
        }
      }
      else if(timeParam == 5){
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
  else if(set == 1){
    if(eventParam==0){
      if(eventProbActive[channel][key+(division*16)] == 0){
        kp.set(key,0);
      }
      if(eventProbActive[channel][key+(division*16)] == 1){
        kp.set(key,1);
      }
    }
    else if(eventParam==1){
      if(eventNote[channel][key+(division*16)] < eventProbSetNote){
        kp.set(key,4);
      }
      if(eventNote[channel][key+(division*16)] > eventProbSetNote){
        kp.set(key,2);
      }
      if(eventNote[channel][key+(division*16)] == eventProbSetNote){
        kp.set(key,1);
      }
      if(eventNote[channel][key+(division*16)] == 0){
        kp.set(key,0);
      }
    }
    else if(eventParam==2){
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
    else if(eventParam==3){
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
    else if(eventParam==4){
      if(eventSlew[channel][key] < eventSetSlew){
        kp.set(key,4);
      }
      if(eventSlew[channel][key] > eventSetSlew){
        kp.set(key,2);
      }
      if(eventSlew[channel][key] == eventSetSlew){
        kp.set(key,1);
      }
      if(eventSlew[channel][key] == 0){
        kp.set(key,0);
      }
    }
    else if(eventParam==5){
      int revKey = ((3-(key/4))*4)+(key%4);
      if(eventQuantMode[channel] == 0){
        int t = (eventQuantMode[channel]) * 16;
        if(revKey < 12){
          if(eventQuant[channel][revKey+t] == 0){kp.set(key,0);}
          if(eventQuant[channel][revKey+t] == 1){kp.set(key,1);}
        }
        else{
          kp.set(key,0);
        }
      }
      else{
        int t = (eventQuantMode[channel]-1) * 16;
        if(eventQuant[channel][revKey+t] == 0){kp.set(key,0);}
        if(eventQuant[channel][revKey+t] == 1){kp.set(key,1);}
      }
    }
    else if(eventParam==6){
      if(eventDiv[channel][key] < eventDivision){
        kp.set(key,4);
      }
      if(eventDiv[channel][key] > eventDivision){
        kp.set(key,2);
      }
      if(eventDiv[channel][key] == eventDivision){
        kp.set(key,1);
      }
      if(eventDiv[channel][key] == 0){
        kp.set(key,0);
      }
    }
    else if(eventParam==7){
      if(eventSizeMin[channel] == key + (division*16)){
        kp.set(eventSizeMin[channel]%16,4);
      }
      else if(eventSizeMax[channel] == key + (division*16)){
        kp.set(eventSizeMax[channel]%16,2);
      }
      else if(key+(division*16) < eventSizeMax[channel] && key+(division*16) > eventSizeMin[channel]){
        kp.set(key,7);
      }
      else{kp.set(key,0);}
    }
  }
}

void Gen::drawMatrixLED(){
  for(int i=0;i<16;i++){drawKey(i);}
  writeNewPosition();
  showLEDS = 1;
}

void Gen::drawMenu(){
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
    if(selParam == 1){if(eventMenuParam == 2){oled.invertedText=1;}}
    oled.drawText(0,3,oled.invertedText,"Skip:" + eventSkipName[eventSkip[channel]]);
    oled.invertedText = 0;
    if(selParam == 0){oled.drawBox(0,(eventMenuParam+1)*8,128,8,0);}
  }
}