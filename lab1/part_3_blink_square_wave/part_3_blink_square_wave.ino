#define REG_PIOC_PER (* (volatile unsigned long *)0x400E1200) //PIO ENABLE REGISTER
#define REG_PIOC_OER (* (volatile unsigned long *)0x400E1210) //OUTPUT ENABLE REGISTER
#define REG_PIOC_MDDR (* (volatile unsigned long *)0x400E1254) //MULTI-DRIVER DISABLE REGISTER
#define REG_PIOC_WPMR (* (volatile unsigned long *)0x400E12E4) //WRITE PROTECT MODE REGISTER

#define REG_PIOC_SODR (* (volatile unsigned long *)0x400E1230) //SET OUTPUT DATA REGISTER
#define REG_PIOC_CODR (* (volatile unsigned long *)0x400E1234) //CLEAR OUTPUT DATA REGISTER
#define REG_PIOC_ODSR (* (volatile unsigned long *)0x400E1238) 
#define pio50_msk  (1<<13) //BIT 30
#define pio51_msk  (1<<12) //BIT 30


void setup() {
  // put your setup code here, to run once:
  REG_PIOC_WPMR = 0x50494F00; //disable WRITE PROTECT MODE REGISTER
  REG_PIOC_PER = pio50_msk | pio51_msk; //set PIO STATUS REGISTER
 
  REG_PIOC_OER = pio50_msk | pio51_msk; //set OUTPUT STATUS REGISTER
  REG_PIOC_MDDR = pio50_msk | pio51_msk; //clear MULTI-DRIVER STATUS REGISTER
  
}

void loop() {
  // put your main code here, to run repeatedly:
  REG_PIOC_ODSR = pio50_msk; //set
  delay(1);
  REG_PIOC_ODSR = pio51_msk; //clear
  delay(1);
}
