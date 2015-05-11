#define  XTC    TC0       // TC number
#define  XCHAN  0         // TC channel
#define  XID    ID_TC0    // Instance ID
#define  PIN    22
#define  PINCHAN  26      // Digital pin 22 which is on PIOB channel 26

void setup() {
  unsigned int chanmask = (1 << PINCHAN);
      
  Serial.begin(9600);
  
  // set PIO to chan B
  //REG_PIOB_PDR = chanmask; //disable pio control,enable peripheral control
  //REG_PIOB_OER = chanmask; //output enable
  //REG_PIOB_ABSR = chanmask; //AB select
  //REG_PIOB_MDDR = chanmask; //multi-driver disable
  
  // set up TC
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID);
  
  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_TCCLKS_XC0);
  TC_Start(XTC, XCHAN); 
  
  pinMode(PIN, INPUT);
}

void dreg(char *s, unsigned int r) {
  Serial.print(s);
  Serial.print(r, HEX);
}

void loop() {
  dreg("\nCV: ", XTC->TC_CHANNEL[XCHAN].TC_CV);
  delay(1000);
}
