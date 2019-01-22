int pS_selected=0;
int pS_selected_o = 0;
int pS_probs[4][16];
bool pS_gate[4];
int pS_prob = 5;
int pS_set = 0;
int pS_pos = 0;

void probSeq(){
  pS_midi_test();
  if(key_pressed == 1){
    for(int i=0;i<16;i++){
      if(key[i]==1){
        pS_probs[pS_selected][i] = pS_prob;
        u8x8.setInverseFont(1);
        u8x8.drawString(((i%4)*2)+((pS_selected%2)*8),((i/4)*1)+((pS_selected/2)*4)+8,String(dectohex(pS_probs[pS_selected][i])+" ").c_str());
        u8x8.setInverseFont(0);
      }
    }
  }
  if(b1_released== 1){}
  if(b2_released == 1){
    pS_selected+= 1;
    pS_selected%= 4;
    pS_draw1Matrix(pS_selected_o);
    pS_draw1Matrix(pS_selected);
    pS_selected_o = pS_selected;
  }
  if(b2_held == 1){
    for(int i=0;i<16;i++){
      pS_probs[pS_selected][i] = pS_prob;
      u8x8.setInverseFont(1);
      u8x8.drawString(((i%4)*2)+((pS_selected%2)*8),((i/4)*1)+((pS_selected/2)*4)+8,String(dectohex(pS_probs[pS_selected][i])+" ").c_str());
      u8x8.setInverseFont(0);
    }
  }
  if(enc_released == 1){
    pS_set += 1;
    pS_set %= 1;
  }
  if(enc_status != 0){
    if(pS_set == 0){
      pS_prob += enc_status;
      if(pS_prob>10){pS_prob = 10;}
      if(pS_prob<0){pS_prob = 0;}
      u8x8.setInverseFont(1);
      u8x8.drawString(0,1,String("Prb:" + dectohex(pS_prob)).c_str());
      u8x8.setInverseFont(0);
    }
  }
  if(oled_draw_bg == 1){pS_drawBg();}
}

void pS_drawBg(){
  pS_drawMatrix();
  pS_drawInfo();
}

void pS_draw1Matrix(int k){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(k==pS_selected){u8x8.setInverseFont(1);}
      u8x8.drawString((i*2)+((k%2)*8),(j*1)+((k/2)*4)+8,String(dectohex(pS_probs[k][(i%4)+(j*4)])+" ").c_str());
      u8x8.setInverseFont(0);
    }
  }
}

void pS_drawMatrix(){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      for(int k=0;k<4;k++){
        if(k==pS_selected){u8x8.setInverseFont(1);}
        u8x8.drawString((i*2)+((k%2)*8),(j*1)+((k/2)*4)+8,String(dectohex(pS_probs[k][(i%4)+(j*4)])+" ").c_str());
        u8x8.setInverseFont(0);
      }
    }
  }
}

void pS_drawInfo(){
  u8x8.drawString(0,0,String("Pos:" + dectohex(pS_pos)).c_str());
  if(pS_set == 0){
    u8x8.setInverseFont(1);
  }
  u8x8.drawString(0,1,String("Prb:" + dectohex(pS_prob)).c_str());
  u8x8.setInverseFont(0);
}

void pS_midi_test(){
  if(midiclock == 1){
    midiclock = 0;
    trellis.clrLED(pS_pos);
    pS_pos += 1;
    pS_pos %= 16;
    trellis.setLED(pS_pos);
    u8x8.drawString(0,0,String("Pos:" + dectohex(pS_pos)).c_str());
    for(int i=0;i<4;i++){
      pS_gate[i] = 0;
      if(pS_probs[i][pS_pos] > random(10)){
        pS_gate[i] = 1;
      }
    }
    for(int i=0;i<4;i++){
      if(pS_gate[i] == 1){
        usbMIDI.sendNoteOn(60,60,i+4);
      }
      if(pS_gate[i] == 0){
        usbMIDI.sendNoteOff(60,0,i+4);
      }
    }
  }
}
