#include <EtherCard.h>
#include <IPAddress.h>
static byte myip[] = { 192,168,0,40 };
static byte gwip[] = { 192,168,0,1 };
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

void ClockWise();
void AntiClockWise();
int pin1 = 4;
int pin2 = 5;
int pin3 = 6;
int pin4 = 7;
int loopNo = 0;
int Speed = 4;
int Direction =0;
int flag = 0;
//bool Move = true;


void udpSerialPrint(word port, byte ip[4], const char *data, word len) {
  IPAddress src(ip[0], ip[1], ip[2], ip[3]);
  Serial.println(data);
  if(strcmp(data,"on") == 0){
    //ClockWise();
    flag = 1;
    Serial.println("on");
    }

  if(strcmp(data,"off") == 0){
    //ClockWise();
    flag = 0;
    Serial.println("off");
    }
    
    if(strcmp(data,"left") == 0){
    //AntiClockWise();

    flag = 2;
    Serial.println("left");
    }
    
    if(strcmp(data,"right") == 0){
    //ClockWise();
    
    
    flag = 1;
    Serial.println("right");
    }
    
    
    
 /*   
   else if(strcmp(data,"left") == 0){
      Serial.println("left");
    
      ClockWise();
    }
    
    else if(strcmp(data,"right") == 0){
      Serial.println("right");
      AntiClockWise();
    }
  
  else if(strcmp(data,"off") == 0){
  Serial.println("off");
  
  //Stop();
  }*/

}
void setup(){
  Serial.begin(57600);
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");
  ether.staticSetup(myip, gwip);
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
  ether.udpServerListenOnPort(&udpSerialPrint, 5000);
      
 pinMode(pin1, OUTPUT);
 pinMode(pin2, OUTPUT);
 pinMode(pin3, OUTPUT);
 pinMode(pin4, OUTPUT); 
 
}

void loop(){
  ether.packetLoop(ether.packetReceive()); 
  if (flag == 1){ClockWise();}
  else if(flag == 2) {AntiClockWise();}
  else if (flag == 0) {}
}

void ClockWise(){  
     if(loopNo ==1){
   digitalWrite(pin1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, LOW);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, HIGH);   // turn the LED on (HIGH is the voltage level)
   }
     else if(loopNo ==2){
   digitalWrite(pin1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, LOW);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, HIGH);   // turn the LED on (HIGH is the voltage level)
   }
    else if(loopNo ==3){
   digitalWrite(pin1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, HIGH);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, LOW);   // turn the LED on (HIGH is the voltage level)
   }
     else if(loopNo ==4){
   digitalWrite(pin1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, HIGH);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, LOW);   // turn the LED on (HIGH is the voltage level)
   loopNo = 0;
 }
   loopNo++;
   for ( int i = 1 ; i<=Speed ; i++)
    {
      if (Speed < 6){delay(60);break;}
      delay(10); 
    }
}


void AntiClockWise()
{
     if(loopNo ==1){
   digitalWrite(pin1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, HIGH);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, LOW);   // turn the LED on (HIGH is the voltage level)
   
 }
   else if(loopNo ==2){
   digitalWrite(pin1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, HIGH);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, LOW);   // turn the LED on (HIGH is the voltage level)
   }
     else if(loopNo ==3){
   digitalWrite(pin1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, LOW);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, HIGH);   // turn the LED on (HIGH is the voltage level)
   }
     else if(loopNo ==4){
   digitalWrite(pin1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin2, LOW);   // turn the LED on (HIGH is the voltage level)
     digitalWrite(pin3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin4, HIGH);   // turn the LED on (HIGH is the voltage level)
      loopNo = 0;
   }
   loopNo++;
   for ( int i = 1 ; i<=Speed ; i++)
    {
      if (Speed < 6){delay(60);break;}
      delay(10); 
    }
}
