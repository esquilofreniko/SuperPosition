int pS_selected= 0;
int pS_probs[4][16];
int pS_prob = 5;
int pS_set = 0;

void probSeq(){
  if(key_pressed == 1){
    for(int i=0;i<16;i++){
      if(key[i]==1){
        pS_probs[pS_selected][i] = pS_prob;
      }
    }
    u8g2.clearBuffer();
    oled_draw_bg = 1;
  }
  
  if(b1_released== 1){
    
  }
  if(b2_released == 1){
    pS_selected+= 1;
    pS_selected%= 4;
    u8g2.clearBuffer();
    oled_draw_bg = 1;
  }
  if(b2_held == 1){
    for(int i=0;i<16;i++){
      pS_probs[pS_selected][i] = pS_prob;
    }
    u8g2.clearBuffer();
    oled_draw_bg = 1;
  }
  if(enc_released == 1){
    pS_set += 1;
    pS_set %= 1;
    u8g2.clearBuffer();
    oled_draw_bg = 1;
  }
  if(enc_status != 0){
    u8g2.clearBuffer();
    oled_draw_bg = 1;
  }

  if(pS_set == 0){
    u8g2.drawFrame(0,9,30,10);
    if(enc_status != 0){
      pS_prob += enc_status;
      if(pS_prob>10){pS_prob = 10;}
      if(pS_prob<0){pS_prob = 0;}
    }
  }

  //Draw
  if(oled_draw_bg ==1 ){
    //Selected Sequence
    if(pS_selected == 0){u8g2.drawFrame(0,20,(128/2)-1,(108/2));};
    if(pS_selected == 1){u8g2.drawFrame((128/2),20,(128/2)-1,(108/2));};
    if(pS_selected == 2){u8g2.drawFrame(0,(108/2)+19,(128/2)-1,(108/2));};
    if(pS_selected == 3){u8g2.drawFrame((128/2),(108/2)+19,(128/2)-1,(108/2));};
    //Background
    for(int i=0;i<8;i++){
      u8g2.drawLine(i*(128/8)-1, 20, i*(128/8)-1, 128); 
      u8g2.drawLine(0, i*(108/8)+20, 128, i*(108/8)+20); 
    }
    //Info Text
    for (int i=0;i<16;i++){
      u8g2.setCursor((i%4)*(128/8)+1,int(i/4)*(108/8)+10+20);
      u8g2.print(pS_probs[0][i]);
      u8g2.setCursor((i%4)*(128/8)+1+(128/2),int(i/4)*(108/8)+10+20);
      u8g2.print(pS_probs[1][i]);
      u8g2.setCursor((i%4)*(128/8)+1,int(i/4)*(108/8)+10+20+(108/2));
      u8g2.print(pS_probs[2][i]);
      u8g2.setCursor((i%4)*(128/8)+1+(128/2),int(i/4)*(108/8)+10+20+(108/2));
      u8g2.print(pS_probs[3][i]);
    }
    u8g2.setCursor(0,8);
    u8g2.print("Probability Sequencer" );
    u8g2.setCursor(0,16);
    u8g2.print("Prob:" + dectohex(pS_prob));
    u8g2.sendBuffer();
  }
}
