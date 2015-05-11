//#include <SoftwareSerial.h>                         // Software Serial Port

//#define RxD         7
//#define TxD         6
#define blueToothSerial Serial2
#define PINBUTTON   13                              // pin of button

#define DEBUG_ENABLED  1

String retSymb   = "+RTINQ=";                       // start symble when there's any return
String slaveName = ";XJTU";                 // caution that ';'must be included, and make sure the slave name is right.

int nameIndex = 0;
int addrIndex = 0;

String recvBuf;
String slaveAddr;

String connectCmd = "\r\n+CONN=";

//SoftwareSerial blueToothSerial(RxD,TxD);

int data = 0;
int datarec;

void setup()
{
    Serial.begin(9600);
    //pinMode(RxD, INPUT);
    //pinMode(TxD, OUTPUT);
    pinMode(PINBUTTON, INPUT);
    
    setupBlueToothConnection();
    //wait 1s and flush the serial buffer
    delay(1000);
    Serial.flush();
    blueToothSerial.flush();
    
    
    Serial2.print(data);
}

void loop()
{
    
    while(Serial2.available()){
      
      datarec = Serial2.parseInt();
      Serial.print(datarec);
      Serial2.print(datarec);
    
    }
    
    
 /*   
    
    static unsigned char state = 0;             // led off
    
    if(digitalRead(PINBUTTON))
    {
        state = 1-state;
        
        Serial.println("button on");
        
        blueToothSerial.print(state);
        
        delay(10);
        while(digitalRead(PINBUTTON))       // until button release
        {
            delay(10);
        }
        
        Serial.println("button off");
    }
    */
}


void setupBlueToothConnection()
{
    blueToothSerial.begin(38400);                               // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("\r\n+STWMOD=1\r\n");                 // set the bluetooth work in master mode
    blueToothSerial.print("\r\n+STNA=Group8\r\n");       // set the bluetooth name as "SeeedBTMaster"
    blueToothSerial.print("\r\n+STAUTO=1\r\n");                 // Auto-connection is forbidden here
    delay(2000);                                                // This delay is required.
    blueToothSerial.flush();
    blueToothSerial.print("\r\n+INQ=1\r\n");                    //make the master inquire
    Serial.println("Master is inquiring!");
    delay(2000); // This delay is required.

    //find the target slave
    char recvChar;
    while(1)
    {
        if(blueToothSerial.available())
        {
            recvChar = blueToothSerial.read();
            recvBuf += recvChar;
            nameIndex = recvBuf.indexOf(slaveName);             //get the position of slave name
            
                                                                //nameIndex -= 1;
                                                                //decrease the ';' in front of the slave name, to get the position of the end of the slave address
            if ( nameIndex != -1 )
            {
                //Serial.print(recvBuf);
                addrIndex = (recvBuf.indexOf(retSymb,(nameIndex - retSymb.length()- 18) ) + retSymb.length());//get the start position of slave address
                slaveAddr = recvBuf.substring(addrIndex, nameIndex);//get the string of slave address
                break;
            }
        }
    }
    
    //form the full connection command
    connectCmd += slaveAddr;
    connectCmd += "\r\n";
    int connectOK = 0;
    Serial.print("Connecting to slave:");
    Serial.print(slaveAddr);
    Serial.println(slaveName);
    //connecting the slave till they are connected
    
    do
    {
        blueToothSerial.print(connectCmd);//send connection command
        recvBuf = "";
        while(1)
        {
            if(blueToothSerial.available()){
                recvChar = blueToothSerial.read();
                recvBuf += recvChar;
                if(recvBuf.indexOf("CONNECT:OK") != -1)
                {
                    connectOK = 1;
                    Serial.println("Connected!");
                    blueToothSerial.print("Connected!");
                    break;
                }
                else if(recvBuf.indexOf("CONNECT:FAIL") != -1)
                {
                    Serial.println("Connect again!");
                    break;
                }
            }
        }
    }while(0 == connectOK);
}
