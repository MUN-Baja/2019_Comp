#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package
{
  int id=1;
  float temperature = 18.3;
  char  text[100] = "Text to be transmitted";
};


typedef struct package Package;
Package data;
//char ack[32];

void setup()
{
  Serial.begin(115200);
  delay(1000);
  
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe(addresses[0]);
  myRadio.stopListening();

//  myRadio.openReadingPipe(1, addresses[1]);
  delay(1000);
}

void loop()
{
  delay(5);
  Serial.println("sending data");
  myRadio.write(&data, sizeof(data)); 

//  delay(5);
//  myRadio.startListening();
//  while(!myRadio.available());
//  myRadio.read( &ack, sizeof(ack) );
//  Serial.println(ack);

  data.id = data.id + 1;
  data.temperature = data.temperature+0.1;
  delay(1000);
}
