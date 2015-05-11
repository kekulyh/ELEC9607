#define BITSPERCHAR 8
#define BAUD 9600

typedef enum
{
  IDLE = 0U,
  START,
  BYTE,
  STOP,
} HIJACK_State_t;

int led = 13;

//* FSM variables */
static HIJACK_State_t txState = IDLE;
static unsigned char txBitn;
static unsigned char txData;
unsigned char txSym = 1;
unsigned char txStart = 0;

void hjisr()
{
/* First iteration check for symbol. */
  digitalWrite(led, txSym);
  
  switch(txState)
  {
    case START:
      txSym = 0;
      txBitn = 0;
      txState = BYTE;
      break;
    case BYTE:
      txSym = txData & 0x01;
      txData = txData >> 1;
      txBitn++;
      txState = txBitn < BITSPERCHAR ? BYTE : STOP;
      break;
    case STOP:
      txData = 0;
      txSym = 1;
      txState = IDLE;
      txStart = 0;
      break;
    case IDLE:
      txSym = 1;
      if (txStart != 0)
        txState = START;
      break;
    default:
        break;
  }
}

void setup()
{
  pinMode(led, OUTPUT);
}

void loop()
{
  int i;
  char b = 0x12;
  if (txStart == 0) {
    txData = b;
    txStart = 1;
  }

  while(txState != IDLE){
    hjisr();
    delayMicroseconds((int)(1000000/BAUD));
  }

  hjisr();
  delayMicroseconds((int)(1000000/BAUD));

  delay(20);
}
