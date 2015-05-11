#define  XTC    TC1       // TC number
#define  XCHAN  1         // TC channel
#define  XID    ID_TC4    // Instance ID
  

double f = VARIANT_MCK / 128; //current frequency

void setup(){
  Serial.begin(9600);
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID);
  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_Start(XTC, XCHAN);
}

void sprint(char *s) {
  Serial.print(s);
}

void fprint(double f) {
  Serial.println(f);
}

void loop(){
  double count0 = 0;
  double count1 = 0;
  double count2 = 0;
  double t1 = 0;
  double t2 = 0;
  count0 = (double)TC_ReadCV(XTC, XCHAN);
  sprint("HELLO");
  count1 = (double)TC_ReadCV(XTC, XCHAN);
  t1 = (count1-count0) * 1000000 / f;
  fprint(1.2);
  count2 = (double)TC_ReadCV(XTC, XCHAN);
  t2 = (count2-count1) * 1000000 / f;
  //t = (b-a)*1000000 / f; //time in microseconds
  Serial.println(t1);
  Serial.println(t2);
  //delay(500);
  //Serial.println(TC_ReadCV(XTC, XCHAN), DEC);
}
