#define REG_PIOC_PER (* (volatile unsigned long *)0x400E1200) //PIO ENABLE REGISTER
#define REG_PIOC_OER (* (volatile unsigned long *)0x400E1210) //OUTPUT ENABLE REGISTER
#define REG_PIOC_MDDR (* (volatile unsigned long *)0x400E1254) //MULTI-DRIVER DISABLE REGISTER
#define REG_PIOC_WPMR (* (volatile unsigned long *)0x400E12E4) //WRITE PROTECT MODE REGISTER

#define REG_PIOC_SODR (* (volatile unsigned long *)0x400E1230) //SET OUTPUT DATA REGISTER
#define REG_PIOC_CODR (* (volatile unsigned long *)0x400E1234) //CLEAR OUTPUT DATA REGISTER

#define pio_msk  (1<<30) //BIT 30

void setup() {
  // put your setup code here, to run once:
  REG_PIOC_WPMR = 0x50494F00; //disable WRITE PROTECT MODE REGISTER
  REG_PIOC_PER = pio_msk; //set PIO STATUS REGISTER
  REG_PIOC_OER = pio_msk; //set OUTPUT STATUS REGISTER
  REG_PIOC_MDDR = pio_msk; //clear MULTI-DRIVER STATUS REGISTER
}

void loop() {
  // put your main code here, to run repeatedly:
  REG_PIOC_SODR = pio_msk; //set
  delay(1000);
  REG_PIOC_CODR = pio_msk; //clear
  delay(1000);
}
