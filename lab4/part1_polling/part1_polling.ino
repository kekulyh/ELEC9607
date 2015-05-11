#define usart1_input 17
#define usart1_output 16

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(38400);
  
  REG_USART1_MR |= US_MR_CHMODE_LOCAL_LOOPBACK;
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial2.print("HELLO");
    char data;
    while ( Serial2.available()){
    data = Serial2.read();    
    Serial.print(data);
    }
    delay(500);  
}
