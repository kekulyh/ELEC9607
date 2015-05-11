#define  XTC    TC1       // TC number
#define  XCHAN  1         // TC channel
#define  XID    ID_TC4    // Instance ID

void setup(){
  Serial.begin(9600);
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID);
  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_Start(XTC, XCHAN);
}
void loop(){
  TC_Start(XTC, XCHAN); //reset and start
  delay(1000); 
  Serial.println(TC_ReadCV(XTC, XCHAN), DEC);
}
