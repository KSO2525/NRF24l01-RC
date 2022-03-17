//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN; CSN = 6 for nano, 8 for uno

//address through which two modules communicate.
const byte address[6] = "00001";
  
  
void setup()
{
  //while (!Serial){
    Serial.begin(9600);
  
  //radio.setChannel(120);
  radio.begin();
  
  
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
    int x_val;
    int y_val;
    radio.read(&x_val, sizeof(x_val));
    
    radio.read(&y_val, sizeof(y_val));
    Serial.println(" ");
    Serial.print("X: ");
    Serial.print(x_val);
    Serial.print("   Y: ");
    Serial.print(y_val);
  }

  //else;
    //Serial.println("NONE");
  
}
