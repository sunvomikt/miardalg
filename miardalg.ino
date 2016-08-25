int midio=2;
int poti;
int major;
int gap;
int score[20][3] = {0};  
int midich=0x01;
void setup() {
  Serial1.begin(31250);
  //pinMode(midio, OUTPUT);
  randomSeed(analogRead(0));

}

void loop() {
  initScore();
  for(int i=0;i<20;i++)
   {
    poti = ((analogRead(A0)*3)/10);
    noteOn(score[i][0], score[i][1], score[i][2]);
    delay(poti+200);
    noteOff(score[i][1]);
    delay(poti+200);
   }
   noteOn(0xFF,0,0);
}
void initScore(){

  major=random(0,4)+1;
  gap=10*major;
  for(int i=0;i<20;i++)
   {
   score[i][0]=0x90;
   if(i==0 or score[i-1][1]>127 or score[i-1][1]<0) { score[i][1]=random(0,127); }
   else { score[i][1]=score[i-1][1]+(random(-1,1)*gap); }   
   //fixed velocity for now
   score[i][2]=0x45;
   //Serial.println(score[i-1][1]);
   //Serial.println(score[i][1]);
   }
  
  //EFFECT 1, MIRRORING THE WHOLE THING 
  for(int i=0;i<10;i++)
  {
   score[20-i][1]=score[i][1];    
  }
  
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




