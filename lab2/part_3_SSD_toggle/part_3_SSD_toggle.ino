#define SSDSIZE 7       // number of segments in SSD
#define DIGSIZE 10      // number of different symbols to decode

volatile int inputpin = 9;
volatile unsigned int state = 1;
volatile unsigned int inum = 1000;

int ssdtab[DIGSIZE][SSDSIZE] =
    {{1,1,1,1,1,1,0},  // = 0
     {0,1,1,0,0,0,0},  // = 1
     {1,1,0,1,1,0,1},  // = 2
     {1,1,1,1,0,0,1},  // = 3
     {0,1,1,0,0,1,1},  // = 4
     {1,0,1,1,0,1,1},  // = 5
     {1,0,1,1,1,1,1},  // = 6
     {1,1,1,0,0,0,0},  // = 7
     {1,1,1,1,1,1,1},  // = 8
     {1,1,1,1,0,1,1}   // = 9
   };

#define  ssdpin(i)  (i+2) // a to pin 2, b to pin 3 etc so the pin offset is +2

void ssddecode(int a)
{
  int j;

  for (j = 0; j < SSDSIZE; j++)
    digitalWrite(ssdpin(j),  ssdtab[a][j] == 1 ? HIGH : LOW);
}

void irq(){
  state = !state;
}

void loop() {
  if(inum >= 2000){
    inum == 1000;
  }
  else if(inum <= 1000 ){
    inum == 1999;
  }
  if(state==0){
    inum--;
  }
  else if(state==1){
      inum++;
  }
  ssddecode(inum % 10);
  delay(1000);
  
}

// the setup routine runs once when you press reset:
void setup() {
  int  j;

  for (j = 0; j < SSDSIZE; j++)
    pinMode(ssdpin(j), OUTPUT);
  
  pinMode(inputpin, INPUT);  
  attachInterrupt(inputpin, irq, FALLING);
}
