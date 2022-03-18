//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN; CSN = 6 for nano, 8 for uno

//address through which two modules communicate.
const byte address[6] = "00001";//use whatever address as long as it's 32 bit or less
int x1;
int y1;

struct MY_DATA{
  int x1;
  int y1;
};
MY_DATA data;

void setup()
{
  //while (!Serial){
    Serial.begin(9600);
  
  //radio.setChannel(120);
  radio.begin();
  radio.powerUp();
  
  //set the address
  
  radio.openReadingPipe(0, address);
  //radio.setPALevel(RF24_PA_MIN);
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    radio.read(&data, sizeof(MY_DATA));
    x1 = data.x1;
    y1 = data.y1;
    Serial.println(" ");
    Serial.print("X: ");
    Serial.print(x1);
    Serial.print("   Y: ");
    Serial.print(y1);
  }

  //else;
    //Serial.println("NONE");
  
}
