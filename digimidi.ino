int midio=2;
int note=-1;
int note2=-1;
int note3=-1;
int note4=-1;
int poti;
int major;
int themelen;
int steps;
int gap;
int desc;
void setup() {
  //  Set MIDI baud rate:
  Serial1.begin(31250);
  pinMode(midio, OUTPUT);
  randomSeed(analogRead(0));

}

void loop() {
  steps=0;
  themelen=random(5)+5;
  if (random(1)==0) {desc=-1;}
  else {desc=1;}
  poti = analogRead(A0);
  poti=((poti*3)/10);
  major=random(5)+1;
  gap=10*major;
  //note=poti;
  if (note<gap or note2<gap or note3<gap) 
  {
    note=(random(120));
    note2=note+random(5)*gap;
    note3=note+(random(5)*gap);
    note4=note+(random(5)*gap);
  }
  else
  {
    note=note-gap;
    note2=note-gap;
    note3=note2-gap;
    note4=note2-gap;
  }
  Serial.println("Made a theme with gap "+String(gap)+", major "+String(major)+" and length of "+String(themelen)+". Tempo:"+String(poti));
  
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  noteOn(0x90, note, 0x60);
  noteOn(0x90, note+2*gap, 0x60);
  for (int note = 0x1E; steps < themelen; note ++ && steps++) {
    //note=note+note;

    
    

    noteOn(0x90, note2, 0x60);
    
    delay(poti);
    if (random(10)>5) { 
    noteOn(0x90, note3, random(100));   
    }
    if (random(10)>5) { 
    noteOn(0x90, note4, random(100));   
    }
    //turning them off
    ;
    delay(poti-random(20));
    noteOn(0x90, note2, 0x00);
    delay(poti+random(20));
    //Serial.println(desc);
    delay(poti-random(20));
    noteOn(0x90, note3, 0x00);
    
    if (random(10)>5) { note=note+(desc*gap);  }
    else { note=note+(random(-1,1)*gap); }
    if (random(10)>5) { note3=note3+(desc*gap);  }
    else { note3=note3+(random(-1,1)*gap); }
    if (random(10)>5) { note2=note2+(desc*gap);  }
    else { note2=note2+(random(-1,1)*gap); }
    
  }
  noteOn(0x90, note, 0x00);
  noteOn(0x90, note+2*gap, 0x00);
  noteOn(0x90, note4, 0x00);
  
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  digitalWrite(midio,cmd);
  digitalWrite(midio,pitch);
  digitalWrite(midio,velocity);
  
  //Serial.println(poti);
  Serial1.write(cmd);//send note on or note off command 
  Serial1.write(pitch);//send pitch data
  Serial1.write(velocity);//send velocity data
}


