#define SSDSIZE 7       // number of segments in SSD
#define DIGSIZE 10      // number of different symbols to decode

#define PIOC_DIFSR (* (volatile unsigned long *)0x400E1284)  //PIO Debouncing Input Filtering Select Register
#define PIOC_SCDR  (* (volatile unsigned long *)0x400E128c)  //PIO Slow Clock Divider Debouncing Register

#define PIOC_DIFSR_MSK (1<<21)  //bit 21
#define PIOC_SCDR_MSK  (1) //

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

unsigned char Key_Scan(void){
  if(PIOC_SCDR == PIOC_SCDR & PIOC_DIFSR_MSK){
    delayMicroseconds(10000);
    if(PIOC_SCDR == PIOC_SCDR & PIOC_DIFSR_MSK){
      while(PIOC_SCDR == PIOC_SCDR & PIOC_DIFSR_MSK);
      return 0;
    }  
  return 1;
  }
}

void irq(){
  if(Key_Scan() == 0){
    inum++;
  }  
}

void loop() {
  ssddecode(inum % 10);
}

// the setup routine runs once when you press reset:
void setup() {
  int  j;

  for (j = 0; j < SSDSIZE; j++)
    pinMode(ssdpin(j), OUTPUT);
    
  pmc_set_writeprotect(false); //disable write protect
  pmc_enable_periph_clk(ID_TC5); //enable TC5
  
  PIOC_DIFSR = PIOC_DIFSR_MSK; //set PIO_IFDGSR=1,debouncing
  
  
  pinMode(inputpin, INPUT);  
  attachInterrupt(inputpin, irq, FALLING);
}
