#define REG_PIOC_PER (* (volatile unsigned long *)0x400E1200) //PIO ENABLE REGISTER
#define REG_PIOC_OER (* (volatile unsigned long *)0x400E1210) //OUTPUT ENABLE REGISTER
#define REG_PIOC_MDDR (* (volatile unsigned long *)0x400E1254) //MULTI-DRIVER DISABLE REGISTER
#define REG_PIOC_WPMR (* (volatile unsigned long *)0x400E12E4) //WRITE PROTECT MODE REGISTER

#define REG_PIOC_SODR (* (volatile unsigned long *)0x400E1230) //SET OUTPUT DATA REGISTER
#define REG_PIOC_CODR (* (volatile unsigned long *)0x400E1234) //CLEAR OUTPUT DATA REGISTER

#define pio_msk  (1<<30) //BIT 30

#define dot 500
#define dash 1500

void setup() {
  // put your setup code here, to run once:
  REG_PIOC_WPMR = 0x50494F00; //disable WRITE PROTECT MODE REGISTER
  REG_PIOC_PER = pio_msk; //set PIO STATUS REGISTER
  REG_PIOC_OER = pio_msk; //set OUTPUT STATUS REGISTER
  REG_PIOC_MDDR = pio_msk; //clear MULTI-DRIVER STATUS REGISTER
}

char *mcodetbl[] = {
  ".-", "-...", "-.-.", "-..", //A-D
  ".", "..-.", "--.", "....", //E-H
  "..", ".---", ".-.-", ".-..", //I-L
  "--", "-.", "---", ".--.", //M-P
  "--.-", ".-.", "...", "-", //Q-T
  "..-", "...-", ".--", "-..-", //U-X
  "-.--", "--.." //Y-Z
};

void mencodechar(char c){
  REG_PIOC_CODR = pio_msk; 
  if(c =='.'){
    delay(dot);
  }
  else{
    delay(dash);
  }
  REG_PIOC_SODR = pio_msk;
  delay(dot * 2);
}

void mencode(char *s) {
  int i = 0; //count
  while ( s[i] != NULL ){
    mencodechar(s[i]);
    i++;
  }
  delay(dash);
}

void loop() {
  // put your main code here, to run repeatedly:
  //char *ch="HELLO";
  //ch = "HELLO";
  char *ch = "HELLO";
  char *curr = ch;
  while (curr != 0)
  {
  mencode(mcodetbl[*curr-'A']);
  curr++;
  }
}
