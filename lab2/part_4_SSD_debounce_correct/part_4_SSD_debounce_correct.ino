#define SSDSIZE 7       // number of segments in SSD
#define DIGSIZE 10      // number of different symbols to decode

volatile int inputpin = 9;
volatile static unsigned inum = 0;

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
  inum++;  
}

void loop() {
  ssddecode(inum % 10);
}

// the setup routine runs once when you press reset:
void setup() {
  int  j;

  for (j = 0; j < SSDSIZE; j++)
    pinMode(ssdpin(j), OUTPUT);
  
 
  pinMode(inputpin, INPUT);  
  attachInterrupt(inputpin, irq, FALLING);
  REG_PIOC_IFDGSR = (1<<21);
  REG_PIOC_IFER = (1<<21);
  REG_PIOC_SCDR = 15;
  
}
