void ProbSeq::run(){
  clock();
  controls();
  if(oled.redraw == 1){drawBg();}
}

void ProbSeq::clock(){
  if(midiclock == 1){
    updatePosition();
    pattMorph(pos);
    output();
    writeNewPosition();
  }
}

void ProbSeq::updatePosition(){
    //Clear Old Position
    midiclock = 0;
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
    //Update Position
    pos += 1;
    pos %= 16;
}

void ProbSeq::writeNewPosition(){
  //Write New Position
  if(patt[selected][pos] == 0){kp.set(pos,6);}
  if(patt[selected][pos] == 1){kp.set(pos,3);}
  kp.show();
}

void ProbSeq::pattMorph(int _pos){
  //Probability Pattern Morph
  if(morph>random(10)){
    for(int i=0;i<4;i++){
      if(probs[i][_pos] > random(10)){
        patt[i][_pos] = 1;
      }
      else{patt[i][_pos] = 0;}
      if(set == 0){
        setPatt(i,_pos);
      }
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
          patt[selected][i] = (patt[selected][i]+1)% 2;
          setPatt(selected,i);
        }
        if(set == 1){
          if(probs[selected][i] != prob){probs[selected][i] = prob;}
          else{probs[selected][i] = 0;}
          setProb(selected,i);
        }
      }
    }
  }
  if(b1.clicked== 1){
    set += 1;
    set %= 2;
    drawInfo();
    for(int i=0;i<4;i++){drawMatrix(i);};
    drawMatrixLED(selected);
  }
  if(b2.clicked == 1){}
  if(b1.held_t == 1){
    for(int i=0;i<16;i++){
      if(set == 0){
        patt[selected][i] = 0;
      }
      if(set == 1){
        probs[selected][i] = 0;
      }
    }
    drawMatrix(selected);
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
    drawMatrix(selected);
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
        drawInfo();
      }
    }
    if(set == 1){
      if(param == 0){
        prob += enc1.rotation;
        if(prob>10){prob = 10;}
        if(prob<0){prob = 0;}
        drawInfo();
        drawMatrixLED(selected);
      }
    }
  }
  if(enc2.rotation != 0){
    selected+= enc2.rotation;
    if(selected>3){selected = 0;}
    if(selected<0){selected = 3;}
    drawMatrix(selected);
    drawMatrixLED(selected);
    drawMatrix(selected_old);
    selected_old = selected;
  }
}

void ProbSeq::drawBg(){
  oled.clear();
  drawInfo();
  for(int i=0;i<4;i++){drawMatrix(i);}
}

void ProbSeq::drawMatrix(int _k){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      oled.invertedText = 0;
      if((i%4)+(j*4) == pos){oled.invertedText = 1;}
      if(set==0){
        oled.drawText((i*1)+(_k*4),(j*1)+4,oled.invertedText,String(dectohex(patt[_k][(i%4)+(j*4)])).c_str());
      }
      if(set==1){
        oled.drawText((i*1)+(_k*4),(j*1)+4,oled.invertedText,String(dectohex(probs[_k][(i%4)+(j*4)])).c_str());
      }
    }
  }
  if(_k==selected){oled.drawBox(_k*32-2,31,33,33);}
}

void ProbSeq::drawMatrixLED(int _k){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(_k == selected){
        if((i%4)+(j*4) != pos){
          if(set==0){
            if(patt[_k][(i%4)+(j*4)] == 0){
              kp.set((i%4)+(j*4),0);
            }
            if(patt[_k][(i%4)+(j*4)] == 1){
              kp.set((i%4)+(j*4),1);
            }
          }
          if(set==1){
            if(probs[_k][(i%4)+(j*4)] < prob){
              kp.set((i%4)+(j*4),4);
            }
            if(probs[_k][(i%4)+(j*4)] > prob){
              kp.set((i%4)+(j*4),2);
            }
            if(probs[_k][(i%4)+(j*4)] == 0){
              kp.set((i%4)+(j*4),0);
            }
            if(probs[_k][(i%4)+(j*4)] == prob){
              kp.set((i%4)+(j*4),1);
            }
          }
        }
      }
    }
  }
  kp.show();
}

void ProbSeq::setPatt(int _i, int _pos){
  if(_i == selected){oled.invertedText=1;}
  oled.drawText((_pos%4)+(_i*4),(_pos/4)+4,oled.invertedText,String(dectohex(patt[_i][_pos])).c_str());
  if(_i == selected){
    if(patt[_i][_pos] == 0){
      kp.set(_pos,0);
    }
    if(patt[_i][_pos] == 1){
      kp.set(_pos,1);
    }
    kp.show();
  }
  oled.invertedText=0;
}

void ProbSeq::setProb(int _i, int _pos){
  if(_i == selected){oled.invertedText=1;}
  oled.drawText((_pos%4)+(_i*4),(_pos/4)+4,oled.invertedText,String(dectohex(probs[_i][_pos])).c_str());
  if(_i == selected){
    if(probs[_i][_pos] != prob){
      kp.set(_pos,0);
    }
    if(probs[_i][_pos] == prob){
      kp.set(_pos,1);
    }
    kp.show();
  }
  oled.invertedText=0;
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