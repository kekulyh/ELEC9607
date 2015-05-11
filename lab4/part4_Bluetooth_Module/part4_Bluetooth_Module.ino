#define PINLED      13

#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

#define DEBUG_ENABLED  1

void setup()
{
    Serial.begin(9600);
    //pinMode(RxD, INPUT);
    //pinMode(TxD, OUTPUT);
    pinMode(PINLED, OUTPUT);
    LEDOFF();
    
    setupBlueToothConnection();
}

void loop()
{
    char recvChar;
    
    while(1)
    {
        if(Serial2.available())
        {//check if there's any data sent from the remote bluetooth shield
            recvChar = Serial2.read();
            Serial.print(recvChar);
            
            if(recvChar == 'h')
            {
                LEDON();
                Serial.print("ON\n");
            }
            else if(recvChar == 'l')
            {
                LEDOFF();
                Serial.print("OFF\n");
            }
        }
    }
}

void setupBlueToothConnection()
{
    Serial2.begin(38400);                           // Set BluetoothBee BaudRate to default baud rate 38400
    Serial2.print("\r\n+STWMOD=0\r\n");             // set the bluetooth work in slave mode
    Serial2.print("\r\n+STNA=Group8\r\n");    // set the bluetooth name as "SeeedBTSlave"
    Serial2.print("\r\n+STOAUT=1\r\n");             // Permit Paired device to connect me
    Serial2.print("\r\n+STAUTO=0\r\n");             // Auto-connection should be forbidden here
    Serial2.print("\r\n+STPIN=0000\r\n");           
    delay(2000);                                            // This delay is required.
    Serial2.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                            // This delay is required.
    Serial2.flush();
}
