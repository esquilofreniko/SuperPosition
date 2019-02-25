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
    writeNewPosition();
  }
}

void ProbSeq::updatePosition(){
    //Clear Old Position
    if(view == 0){
      if(set == 0){
        if(patt[selected][pos] == 0){kp.set(pos,0);}
        if(patt[selected][pos] == 1){kp.set(pos,1);}
      }
      if(set == 1){
        if(probs[selected][pos] < prob){kp.set(pos,4);}
        if(probs[selected][pos] > prob){kp.set(pos,2);}
        if(probs[selected][pos] == 0){kp.set(pos,0);}
        if(probs[selected][pos] == prob){kp.set(pos,1);}
      }
    }
    if(view == 1){
      if(pos < (selected+1)*4 && pos >= selected*4){
        for(int i=0;i<4;i++){
          if(set == 0){
            if(patt[i][pos] == 0){kp.set((pos%4)+(i*4),0);}
            if(patt[i][pos] == 1){kp.set((pos%4)+(i*4),1);}
          }
          if(set == 1){
            if(probs[i][pos] < prob){kp.set((pos%4)+(i*4),4);}
            if(probs[i][pos] > prob){kp.set((pos%4)+(i*4),2);}
            if(probs[i][pos] == 0){kp.set((pos%4)+(i*4),0);}
            if(probs[i][pos] == prob){kp.set((pos%4)+(i*4),1);}
          }
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
    if(patt[selected][pos] == 0){kp.set(pos,6);}
    if(patt[selected][pos] == 1){kp.set(pos,3);}
  }
  if(view == 1){
    if(pos < (selected+1)*4 && pos >= selected*4){
      for(int i=0;i<4;i++){
        if(patt[i][pos] == 0){kp.set((pos%4) + (i*4),6);}
        if(patt[i][pos] == 1){kp.set((pos%4) + (i*4),3);}
      }
    }
  }

  kp.show();
}

void ProbSeq::pattMorph(int _pos){
  //Probability Pattern Morph
  if(morph>random(10)){
    for(int i=0;i<4;i++){
      if(probs[i][_pos] > random(10)){patt[i][_pos] = 1;}
      else{patt[i][_pos] = 0;}
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
    for(int i=0;i<16;i++){
      if(kp.key[i]==1){
        if(set == 0){
          setPatt(selected,i);
        }
        if(set == 1){
          setProb(selected,i);
        }
      }
    }
  }
  if(b1.clicked== 1){
    set += 1;
    set %= 2;
    drawMatrixLED(selected);
  }
  if(b2.clicked == 1){

  }
  if(b1.held_t == 1){
    for(int i=0;i<16;i++){
      if(set == 0){
        patt[selected][i] = 0;
      }
      if(set == 1){
        probs[selected][i] = 0;
      }
    }
    drawMatrixLED(selected);
  }
  if(b2.held_t == 1){
    for(int i=0;i<16;i++){
      if(set == 0){
        patt[selected][i] = 1;
      }
      if(set == 1){
        probs[selected][i] = prob;
      }
    }
    drawMatrixLED(selected);
  }
  if(enc1.clicked == 1){}
  if(enc2.clicked == 1){}
  if(enc1.rotation != 0){
    if(set == 0){
      if(param == 0){
        morph += enc1.rotation;
        if(morph>10){morph=10;}
        if(morph<0){morph=0;}
      }
    }
    if(set == 1){
      if(param == 0){
        prob += enc1.rotation;
        if(prob>10){prob = 10;}
        if(prob<0){prob = 0;}
        drawMatrixLED(selected);
      }
    }
  }
  if(enc2.rotation != 0){
    selected+= enc2.rotation;
    if(selected>3){selected = 0;division++;}
    if(selected<0){selected = 3;division--;}
    if(division>3){division = 0;}
    if(division<0){division = 3;}
    drawMatrixLED(selected);
  }
}

void ProbSeq::setPatt(int _selected, int _pos){
  if(view == 0){
    patt[_selected][_pos] = (patt[_selected][_pos]+1)%2;
    if(patt[_selected][_pos] == 0){kp.set(_pos,0);}
    if(patt[_selected][_pos] == 1){kp.set(_pos,1);}
  }
  if(view == 1){}
  kp.show();
}

void ProbSeq::setProb(int _selected, int _pos){
  if(probs[_selected][_pos] != prob){probs[_selected][_pos] = prob;}
  else{probs[_selected][_pos] = 0;}
  if(probs[_selected][_pos] != prob){kp.set(_pos,0);}
  if(probs[_selected][_pos] == prob){
    kp.set(_pos,1);
  }
  kp.show();
}

void ProbSeq::drawBg(){
  oled.clear();
  drawInfo();
  for(int i=0;i<4;i++){drawMatrix(i);}
  drawDivision();
}

void ProbSeq::drawInfo(){
  if(set == 0){
    if(param == 0){oled.invertedText=1;}
    oled.drawText(0,1,oled.invertedText,String("Mrph:" + dectohex(morph)).c_str());
    oled.invertedText=1;
  }
  oled.drawText(0,0,oled.invertedText,"Patt");
  oled.invertedText = 0;
  if(set == 1){
    if(param == 0){oled.invertedText=1;}
    oled.drawText(0,1,oled.invertedText,String("Prob:" + dectohex(prob)).c_str());
    oled.invertedText=1;
  }
  oled.drawText(4,0,oled.invertedText,String("Prob").c_str());
  oled.invertedText=0;
}

void ProbSeq::drawMatrix(int k){
  if(view == 0){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        oled.invertedText = 0;
        if((i%4)+(j*4) == pos){oled.invertedText = 1;}
        if(set==0){
          oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohex(patt[k][(i%4)+(j*4)]));
        }
        if(set==1){
          oled.drawText((i*1)+(k*4),(j*1)+4,oled.invertedText,dectohex(probs[k][(i%4)+(j*4)]));
        }
      }
    }
  }
  if(view == 1){
    for(int i=0;i<16;i++){
      oled.invertedText = 0;
      if(pos%16 == i){oled.invertedText = 1;}
      if(set==0){
        oled.drawText(i,k+4,oled.invertedText,dectohex(patt[k][i]));
      }
      if(set==1){
        oled.drawText(i,k+4,oled.invertedText,dectohex(probs[k][i]));
      }
    }
  }
  if(k==selected){oled.drawBox(k*32-2,31,33,33,0);}
}

void ProbSeq::drawMatrixLED(int k){
  if(view == 0){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        if((i%4)+(j*4) != pos){
          if(set==0){
            if(patt[k][(i%4)+(j*4)] == 0){
              kp.set((i%4)+(j*4),0);
            }
            if(patt[k][(i%4)+(j*4)] == 1){
              kp.set((i%4)+(j*4),1);
            }
          }
          if(set==1){
            if(probs[k][(i%4)+(j*4)] < prob){
              kp.set((i%4)+(j*4),4);
            }
            if(probs[k][(i%4)+(j*4)] > prob){
              kp.set((i%4)+(j*4),2);
            }
            if(probs[k][(i%4)+(j*4)] == 0){
              kp.set((i%4)+(j*4),0);
            }
            if(probs[k][(i%4)+(j*4)] == prob){
              kp.set((i%4)+(j*4),1);
            }
          }
        }
      }
    }
  }
  if(view == 1){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        if(set == 0){
          if(patt[j][i+(k*4)] == 0){
            kp.set((i%4)+(j*4),0);
          }
          if(patt[j][i+(k*4)] == 1){
            kp.set((i%4)+(j*4),1);
          }
        }
        if(set == 1){
          if(probs[j][i+(k*4)] < prob){
            kp.set((i%4)+(j*4),4);
          }
          if(probs[j][i+(k*4)] > prob){
            kp.set((i%4)+(j*4),2);
          }
          if(probs[j][i+(k*4)] == 0){
            kp.set((i%4)+(j*4),0);
          }
          if(probs[j][i+(k*4)] == prob){
            kp.set((i%4)+(j*4),1);
          }
        }
      }
    }
  }
  writeNewPosition();
  kp.show();
}

void ProbSeq::drawDivision(){
  for(int i=0;i<4;i++){
    if(floor(pos/16)==i){oled.drawText((i*4)+1,3,1,dectohex(i)+" ");}
    else{oled.drawText((i*4)+1,3,0,dectohex(i)+" ");}
  }
  oled.drawBox(division*32,24,32,8,0);
}