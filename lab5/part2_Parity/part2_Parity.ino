#define BITSPERCHAR 8
#define BAUD 9600

volatile boolean state;

typedef enum
{
  IDLE = 0U,
  START,
  BYTE,
  PARITY,
  STOP,
} HIJACK_State_t;

int led = 13;

//* FSM variables */
static HIJACK_State_t txState = IDLE;
static unsigned char txBitn;
static unsigned char txData;
unsigned char txSym = 1;
unsigned char txStart = 0;
static unsigned int count;

void hjisr()
{
/* First iteration check for symbol. */
  digitalWrite(led, txSym);
  
  switch(txState)
  {
    case START:
      txSym = 0;
      txBitn = 0;
      count = 0;
      txState = BYTE;
      break;
    case BYTE:
      txSym = txData & 0x01;
      count += txSym;
      txData = txData >> 1;
      txBitn++;
      txState = txBitn < BITSPERCHAR ? BYTE : PARITY;
      break;
    case PARITY:
      txSym = (char)(count % 2); //even parity      
      txState = STOP;      
      break;
    case STOP:
      txData = 0;
      count = 0;
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

//TC1 ch0
void TC3_Handler()
{
        TC_GetStatus(TC1,0);
        state =! state;
       
        int i;
        char b = 0x52;
        if (txStart == 0) {
            txData = b;
            txStart = 1;
        }
        
        hjisr();
        
}

void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
        pmc_set_writeprotect(false);
        pmc_enable_periph_clk((uint32_t)irq);
        TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
        uint32_t rc = VARIANT_MCK/2/frequency; //2 because we selected TIMER_CLOCK1 above
        TC_SetRA(tc, channel, rc/2); //50% high, 50% low
        TC_SetRC(tc, channel, rc);
        TC_Start(tc, channel);
        
        tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS; //TC Interrupt Enable Register RC Compare Interrupt
        tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS; //TC Interrupt Disable Register
        NVIC_EnableIRQ(irq);
}

void setup()
{
  pinMode(led, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
  startTimer(TC1, 0, TC3_IRQn, BAUD); //TC1 channel 0, the IRQ for that channel and the desired frequency
}

void loop()
{
  char a = 0;
  
  if (Serial1.available() > 0) {
    a = Serial1.read();
    Serial.println(a, HEX);
  }
}
