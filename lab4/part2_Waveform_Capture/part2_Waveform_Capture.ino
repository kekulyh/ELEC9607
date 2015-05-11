#define usart1_input 17
#define usart1_output 16

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400); 
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.print(0x1A);
    delay(50);
}
