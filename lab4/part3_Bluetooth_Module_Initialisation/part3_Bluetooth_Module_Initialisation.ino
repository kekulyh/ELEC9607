#define DEBUG_ENABLED  1

void setup()
{
    Serial.begin(9600);
   
    setupBlueToothConnection();
}

void loop()
{
    char recvChar;
    
    while(1)
    {
        if(Serial2.available())
        {//check if there's any data sent from the remote bluetooth shield
            
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
    delay(2000);                                            // This delay is required.
    Serial2.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                            // This delay is required.
    Serial2.flush();
}
