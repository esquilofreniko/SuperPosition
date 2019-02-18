int pS_selected=0;
int pS_selected_old = 0;
int pS_probs[4][16];
bool pS_patt[4][16];
int pS_prob = 5;
int pS_set = 0;
int pS_param = 0;
int pS_pos = 0;
int pS_morph = 0;

void probSeq(){
  pS_midi();
  if(key_pressed == 1){
    for(int i=0;i<16;i++){
      if(key[i]==1){
        if(pS_set == 0){
          pS_patt[pS_selected][i] = (pS_patt[pS_selected][i]+1)% 2;
          pS_setPatt(pS_selected,i);
        }
        if(pS_set == 1){
          if(pS_probs[pS_selected][i] != pS_prob){pS_probs[pS_selected][i] = pS_prob;}
          else{pS_probs[pS_selected][i] = 0;}
          pS_setProb(pS_selected,i);
        }
      }
    }
  }
  if(b1_released== 1){
    pS_set += 1;
    pS_set %= 2;
    pS_drawInfo();
    for(int i=0;i<4;i++){pS_drawMatrix(i);};
  }
  if(b2_released == 1){

  }
  if(b1_held_t == 1){
    for(int i=0;i<16;i++){
      if(pS_set == 0){
        pS_patt[pS_selected][i] = 0;
      }
      if(pS_set == 1){
        pS_probs[pS_selected][i] = 0;
      }
    }
    pS_drawMatrix(pS_selected);
  }
  if(b2_held_t == 1){
    for(int i=0;i<16;i++){
      if(pS_set == 0){
        pS_patt[pS_selected][i] = 1;
      }
      if(pS_set == 1){
        pS_probs[pS_selected][i] = pS_prob;
      }
    }
    pS_drawMatrix(pS_selected);
  }
  if(enc1_released == 1){
    
    }
  if(enc2_released == 1){
    
    }
  if(enc1_status != 0){
    if(pS_set == 0){
      if(pS_param == 0){
        pS_morph += enc1_status;
        if(pS_morph>10){pS_morph=10;}
        if(pS_morph<0){pS_morph=0;}
        pS_drawInfo();
      }
    }
    if(pS_set == 1){
      if(pS_param == 0){
        pS_prob += enc1_status;
        if(pS_prob>10){pS_prob = 10;}
        if(pS_prob<0){pS_prob = 0;}
        pS_drawInfo();
        pS_drawMatrixLED(pS_selected);
      }
    }
  }
  if(enc2_status != 0){
    pS_selected+= enc2_status;
    if(pS_selected>3){pS_selected = 0;}
    if(pS_selected<0){pS_selected = 3;}
    pS_drawMatrix(pS_selected);
    pS_drawMatrix(pS_selected_old);
    pS_selected_old = pS_selected;
  }
  if(oled_draw_bg == 1){pS_drawBg();}
}

void pS_drawBg(){
  oled_clear();
  pS_drawInfo();
  for(int i=0;i<4;i++){pS_drawMatrix(i);}
  oled_show();
}

void pS_drawMatrix(int k){
  oled_draw_bg = 1;
  if(k==pS_selected){
    oled_drawBox(k*32-2,31,33,33);
  }
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(pS_set==0){
        oled_drawText((i*1)+(k*4),(j*1)+4,invertedText,String(dectohex(pS_patt[k][(i%4)+(j*4)])).c_str());
      }
      if(pS_set==1){
        oled_drawText((i*1)+(k*4),(j*1)+4,invertedText,String(dectohex(pS_probs[k][(i%4)+(j*4)])).c_str());
      }
    }
  }
  pS_drawMatrixLED(k);
}

void pS_drawMatrixLED(int k){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(k == pS_selected){
        if(pS_set==0){
          if(pS_patt[k][(i%4)+(j*4)] == 0){
            kp_set((i%4)+(j*4),0);
          }
          if(pS_patt[k][(i%4)+(j*4)] == 1){
            kp_set((i%4)+(j*4),1);
          }
        }
        if(pS_set==1){
          if(pS_probs[k][(i%4)+(j*4)] < pS_prob){
            kp_set((i%4)+(j*4),4);
          }
          if(pS_probs[k][(i%4)+(j*4)] > pS_prob){
            kp_set((i%4)+(j*4),2);
          }
          if(pS_probs[k][(i%4)+(j*4)] == 0){
            kp_set((i%4)+(j*4),0);
          }
          if(pS_probs[k][(i%4)+(j*4)] == pS_prob){
            kp_set((i%4)+(j*4),1);
          }
        }
      }
    }
  }
  kp_show();
}

void pS_setProb(int _i, int _pos){
  oled_draw_bg = 1;
  oled_drawText(((_pos%4)*2)+((_i%2)*8),((_pos/4)*1)+((_i/2)*4)+8,invertedText,String(dectohex(pS_probs[_i][_pos])).c_str());
  if(_i == pS_selected){
    if(pS_probs[_i][_pos] != pS_prob){
      kp_set(_pos,0);
    }
    if(pS_probs[_i][_pos] == pS_prob){
      kp_set(_pos,1);
    }
    kp_show();
  }
}

void pS_setPatt(int _i, int _pos){
  oled_draw_bg = 1;
  oled_drawText(((_pos%4)*2)+((_i%2)*8),((_pos/4)*1)+((_i/2)*4)+8,invertedText,String(dectohex(pS_patt[_i][_pos])).c_str());
  if(_i == pS_selected){
    if(pS_patt[_i][_pos] == 0){
      kp_set(_pos,0);
    }
    if(pS_patt[_i][_pos] == 1){
      kp_set(_pos,1);
    }
    kp_show();
  }
}

void pS_drawInfo(){
  oled_draw_bg = 1;
  if(pS_set == 0){
    if(pS_param == 0){invertedText=1;}
    oled_drawText(0,1,invertedText,String("Mrph:" + dectohex(pS_morph)).c_str());
    invertedText=0;
    invertedText=1;
  }
  oled_drawText(0,0,invertedText,"Patt");
  invertedText = 0;
  if(pS_set == 1){
    if(pS_param == 0){invertedText=1;}
    oled_drawText(0,1,invertedText,String("Prob:" + dectohex(pS_prob)).c_str());
    invertedText=0;
    invertedText=1;
  }
  oled_drawText(4,0,invertedText,String("Prob").c_str());
  invertedText=0;
}

void pS_midi(){
  if(midiclock == 1){
    //Clear Old Position Display
    midiclock = 0;
    if(pS_set == 0){
      if(pS_patt[pS_selected][pS_pos] == 0){
        kp_set(pS_pos,0);
      }
      if(pS_patt[pS_selected][pS_pos] == 1){
        kp_set(pS_pos,1);
      }
    }
    if(pS_set == 1){
      if(pS_probs[pS_selected][pS_pos] < pS_prob){
        kp_set(pS_pos,4);
      }
      if(pS_probs[pS_selected][pS_pos] > pS_prob){
        kp_set(pS_pos,2);
      }
      if(pS_probs[pS_selected][pS_pos] == 0){
        kp_set(pS_pos,0);
      }
      if(pS_probs[pS_selected][pS_pos] == pS_prob){
        kp_set(pS_pos,1);
      }
    }
    //Update Position
    pS_pos += 1;
    pS_pos %= 16;
    //Probability Pattern Morphing
    if(pS_morph>random(10)){
      for(int i=0;i<4;i++){
        if(pS_probs[i][pS_pos] > random(10)){
          pS_patt[i][pS_pos] = 1;
        }
        else{pS_patt[i][pS_pos] = 0;}
        if(pS_set == 0){
          pS_setPatt(i,pS_pos);
        }
      }
    }
    //Output
    for(int i=0;i<4;i++){
      if(pS_patt[i][pS_pos] == 1){
        usbMIDI.sendNoteOn(60,60,i+4);
      }
      if(pS_patt[i][pS_pos] == 0){
        usbMIDI.sendNoteOff(60,0,i+4);
      }
    }
    //Write New Position Display
    if(pS_patt[pS_selected][pS_pos] == 0){
      kp_set(pS_pos,6);
    }
    if(pS_patt[pS_selected][pS_pos] == 1){
      kp_set(pS_pos,3);
    }
    kp_show();
  }
}
