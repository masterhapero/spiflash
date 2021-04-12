#include <SPI.h>

// Duemilanove pins
#define csPIN 10
#define DATAOUT 11
#define DATAIN 12
#define SPICLOCK 13

/*
// Atmega2560 pins
#define csPIN 53
#define DATAOUT 51
#define DATAIN 50
#define SPICLOCK 52
*/

SPISettings settingsST(10000000,MSBFIRST,SPI_MODE0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();

  Serial.println("Hello ST EEPROM");
  pinMode(csPIN,OUTPUT);
  pinMode(DATAOUT,OUTPUT);
  pinMode(DATAIN,INPUT);
  pinMode(SPICLOCK,OUTPUT);
  digitalWrite(csPIN,HIGH);

}

void doRead()
{
  digitalWrite(csPIN,HIGH);
  delay(100);
  SPI.beginTransaction(settingsST);
  digitalWrite(csPIN,LOW);
  delay(10);
  // Read command
  SPI.transfer(0x03);
  // 16bit address, high byte first
  SPI.transfer(0x00);
  SPI.transfer(0x01);
  char ch[30];
  Serial.println("Read");
  for(unsigned int i = 0; i<128; i++) {
      // Read operation
      byte b = SPI.transfer(0xFF);
      sprintf(ch,"%02X ",b&0xFF);
      Serial.print(ch);
      if(i%32==31)
        Serial.println("");      
  }
    
  SPI.endTransaction();
  digitalWrite(csPIN,HIGH);
}

void doStatus()
{
  digitalWrite(csPIN,HIGH);
  delay(100);
  SPI.beginTransaction(settingsST);
  digitalWrite(csPIN,LOW);
  delay(10);
  // Read command
  SPI.transfer(0x05);
  // 16bit address
  char ch[30];
  Serial.println("Status");
  for(unsigned int i = 0; i<1; i++) {
      // Read operation
      byte b = SPI.transfer(0xFF);
      sprintf(ch,"%02X ",b&0xFF);
      Serial.print(ch);
      if(i%32==31)
        Serial.println("");      
  }
  Serial.println("");      
   
  SPI.endTransaction();
  digitalWrite(csPIN,HIGH);
}


void doWrite()
{
  digitalWrite(csPIN,HIGH);
  delay(100);
  SPI.beginTransaction(settingsST);
  digitalWrite(csPIN,LOW);
  delay(10);
  // Read command
  SPI.transfer(0x02);
  // 16bit address
  SPI.transfer(0x00);
  SPI.transfer(0x01);
  // 8bit data
  SPI.transfer(0x42);
    
  SPI.endTransaction();
  digitalWrite(csPIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
   char letter = Serial.read(); //listening to the serial port
   if(letter == '1')
     doRead();

   if(letter == '2')
     doWrite();     

   if(letter == '3')
     doStatus();     

  }
}
