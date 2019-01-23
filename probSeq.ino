int pS_selected=0;
int pS_selected_old = 0;
int pS_probs[4][16];
bool pS_patt[4][16];
bool pS_gate[4];
int pS_prob = 5;
int pS_set = 0;
int pS_pos = 0;

void probSeq(){
  pS_midi_test();
  if(key_pressed == 1){
    for(int i=0;i<16;i++){
      if(key[i]==1){
        if(pS_set == 0){
          pS_patt[pS_selected][i] = (pS_patt[pS_selected][i]+1)% 2;
          u8x8.setInverseFont(1);
          u8x8.drawString(((i%4)*2)+((pS_selected%2)*8),((i/4)*1)+((pS_selected/2)*4)+8,String(dectohex(pS_patt[pS_selected][i])).c_str());
          u8x8.setInverseFont(0);
        }
        if(pS_set == 1){
          if(pS_probs[pS_selected][i] != pS_prob){pS_probs[pS_selected][i] = pS_prob;}
          else{pS_probs[pS_selected][i] = 0;}
          u8x8.setInverseFont(1);
          u8x8.drawString(((i%4)*2)+((pS_selected%2)*8),((i/4)*1)+((pS_selected/2)*4)+8,String(dectohex(pS_probs[pS_selected][i])).c_str());
          u8x8.setInverseFont(0);
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
    pS_selected+= 1;
    pS_selected%= 4;
    pS_drawMatrix(pS_selected);
    pS_drawMatrix(pS_selected_old);
    pS_selected_old = pS_selected;
  }
  if(b1_held == 1){
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
  if(b2_held == 1){
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
  if(enc_released == 1){

  }
  if(enc_status != 0){
    if(pS_set == 1){
      pS_prob += enc_status;
      if(pS_prob>10){pS_prob = 10;}
      if(pS_prob<0){pS_prob = 0;}
//      u8x8.setInverseFont(1);
//      u8x8.drawString(4,2,String("Prb:" + dectohex(pS_prob)).c_str());
//      u8x8.setInverseFont(0);
      pS_drawInfo();
    }
  }
  if(oled_draw_bg == 1){pS_drawBg();}
}

void pS_drawBg(){
  for(int i=0;i<4;i++){pS_drawMatrix(i);}
  pS_drawInfo();
}

void pS_drawMatrix(int k){
  if(k==pS_selected){u8x8.setInverseFont(1);}
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(pS_set==0){
        u8x8.drawString((i*2)+((k%2)*8),(j*1)+((k/2)*4)+8,String(dectohex(pS_patt[k][(i%4)+(j*4)])).c_str());
      }
      if(pS_set==1){
        u8x8.drawString((i*2)+((k%2)*8),(j*1)+((k/2)*4)+8,String(dectohex(pS_probs[k][(i%4)+(j*4)])).c_str());
      }
    }
  }
  u8x8.setInverseFont(0);
}

void pS_drawInfo(){
  u8x8.drawString(0,0,String("Pos:" + dectohex(pS_pos)).c_str());
  if(pS_set == 0){u8x8.setInverseFont(1);}
  u8x8.drawString(0,2,"Pat");
  u8x8.setInverseFont(0);
  if(pS_set == 1){u8x8.setInverseFont(1);}
  u8x8.drawString(3,2,String("Prb:" + dectohex(pS_prob)).c_str());
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
