int midio=2;
int poti;
int major;
int gap;
int steps;
// score[n] = [COMMAND,NOTE,VELOCITY,LENGTH,CURRENTMS]
int score[20][5] = {0};  
//int score2[20][5] = {0};  
unsigned long cMillis = 0;   
int midich=0x01;
int reinitc=0;
void setup() {
  Serial1.begin(31250);
  //pinMode(midio, OUTPUT);
  randomSeed(analogRead(0));
  initScore(score);
  //ReinitScore(score);
  /*for(int i=0;i<20;i++)
  {
    score2[i][1]=score[i][1];
    score2[i][2]=score[i][2];
  }*/
  //initScore(score2);
}

void loop() {
  //two part - keep track of rounds/steps at ea loop
  // find the note sc[step] to turn on
  // check if enough time passed and turn it off
  poti = ((analogRead(A0)*3)/10);
  cMillis = millis();
  if(steps>19) {
    //we've done a full loop
    noteOn(0xFF,0,0);
    //noteOn(0xFF+midich,0,0);
    ReinitScore(score);
    //ReinitScore(score);
    steps=0;
    }
  
    noteOn(score[steps][0], score[steps][1], score[steps][2]);
    score[steps][4]=cMillis;
    
    //noteOn(score2[i][0], score2[i][1], score2[i][2]);
    //delay(poti+100);
    for(int i=0;i<20;i++)
    {
      if (cMillis - score[i][4] >= score[i][3]) 
      {
      noteOff(score[i][1]);
      }
    
    }

   
   //ReinitScore(score2);
   //ReinitScore(score2);
   steps+=1;
   delay(poti+100);
}
void initScore(int sc[20][5]){
  reinitc=0;
  major=random(0,4)+1;
  gap=10*major;
  for(int i=0;i<20;i++)
   {
   sc[i][0]=0x90;
   if(i==0 or sc[i-1][1]>127 or sc[i-1][1]<0) { sc[i][1]=random(0,127); }
   else { 
     //gap=gap*random(-1,1);
     sc[i][1]=sc[i-1][1]+gap; 
     // arpeggiator sim
     if(random(1,10)<6) { sc[i][1]=sc[i-2][1];}
   }   
   //abs(sin(step)) velocity
   sc[i][2]=abs(sin(i)*100);
   //same but for note length
   sc[i][3]=abs(sin(i)*200)+100;
   }

}

void ReinitScore(int sc[20][5]){

  for(int i=0;i<20;i++)
  {
   if(sc[i][1]<0 or sc[i][1]>120) { sc[i][1]=random(gap,120);}  
   if(sc[i][2]<0 or sc[i][2]>120) { sc[i][2]=random(gap,120);}    
   sc[i][3]=abs(sin(i)*200)+100;
  }  
  
  //EFFECT 2 RNAADODM
  for(int i=1;i<20;i++)
  {
   if(random(1,10)<5) { sc[i][1]=sc[i-1][1]+random(-1,1)*gap;}    
  }  
  
  // EFFECT 4 INSERTING BASE NOTES
  for(int i=0;i<20;i++)
  {
   if(random(1,10)<3) { sc[i][1]=sc[0][1];}    
  } 
  
  //EFFECT 3 ARPEGG SIMU
   if(random(1,10)<3) { 
     sc[3][1]=sc[0][1]+gap;
     sc[4][1]=sc[1][1]+gap;
     sc[5][1]=sc[2][1]+gap;
     sc[6][1]=sc[0][1]+gap;
     sc[7][1]=sc[1][1]+gap;
     sc[8][1]=sc[2][1]+gap;
     }    
  
  //EFFECT 5, LOWERING PITCH
  if(random(1,10)<3) { 
    for(int i=0;i<20;i++)
    {
     sc[i][1]=sc[i][1]-gap;    
    }
  }
  
    
  //EFFECT 1, MIRRORING THE WHOLE THING 
  for(int i=0;i<10;i++)
  {
   sc[i][1]=sc[19-i][1];
   sc[i][2]=sc[19-i][2];    
  }
  
  
  reinitc+=10;
  if (random(0,100)<reinitc) { initScore(sc); }

}

void noteOn(int cmd, int pitch, int velocity) {
  /*digitalWrite(midio,cmd);
  digitalWrite(midio,pitch);
  digitalWrite(midio,velocity);*/
  
  //Serial.println(poti);
  Serial1.write(144+midich);//send note on or note off command 
  Serial1.write(pitch);//send pitch data
  Serial1.write(velocity);//send velocity data
}

void noteOff(int note) {
  /*digitalWrite(midio,0x80);//send note on or note off command 
  digitalWrite(midio,note);//send pitch data
  digitalWrite(midio,0x00);*/
  
  Serial1.write(128+midich);//send note on or note off command 
  Serial1.write(note);//send pitch data
  Serial1.write(0);//send velocity data
}




