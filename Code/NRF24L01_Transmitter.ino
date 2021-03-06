/*
 * 
 */


//Include Libraries
#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//display variables
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };


//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
const int button1 = 6;// button on the joystick
//address through which two modules communicate.
const byte addresses[6] = "00001";//use whatever address you want as long as it's under 32 bit
//variables for joystick
int x1;
int y1;
int x1_mid = 508;
int y1_mid = 516;

struct MY_DATA{
  int x1;
  int y1;
};

MY_DATA data;

void setup()
{
  radio.begin();
  radio.openWritingPipe(addresses);
  radio.stopListening();
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  
  //radio.setChannel(120);
  //radio.powerUp();
  
  //radio.setPALevel(RF24_PA_MIN);
  //set the address
  //pinMode(button1, INPUT);
  
  //Set module as transmitter
}
void loop(){
  //Send message to receiver
  y1 = analogRead(X_pin);
  x1 = analogRead(Y_pin);
  //const char text[] = data;
  if (x1 >= x1_mid - 2 && x1 <= x1_mid + 2){
    x1 = 0;//508
  }
  else if (x1 > x1_mid + 2){
    x1 = (x1 - x1_mid) * 2.01;
    if (x1 >= 1000){
      x1 = 1000;
    }
  }
  else if (x1 < x1_mid - 2){
    x1 = (x1 - x1_mid) * 2.01;
    if (x1 <= -1000){
      x1 = -1000;
    }
  }
  if (y1 >= y1_mid - 2 && y1 <= y1_mid + 2){
    y1 = 0;//516
  }
  else if (y1 > y1_mid + 2){
    y1 = (y1 - y1_mid) * 1.98;
    if (y1 >= 1000){
      y1 = 1000;
    }
  }
  else if (y1 < y1_mid - 2){
    y1 = (y1 - y1_mid) * 1.98;
    if (y1 <= -1000){
      y1 = -1000;
    }
  }  
  data.x1 = x1;
  data.y1 = y1;
  Serial.println(" ");
  Serial.print("X: ");
  Serial.print(data.x1);
  Serial.print("   Y: ");
  Serial.print(data.y1);
  //Serial.println(radio.write(&text, sizeof(text)));
  radio.write(&data, sizeof(MY_DATA));
  screen_ball();
  
}
void screen_ball(){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 2);
  display.write("Everything Remote");
  display.setCursor(2, 18);
  display.write("X1: ");
  display.print(x1);
  display.setCursor(2, 26);
  display.write("Y1: ");
  display.print(y1);
  display.display();
}
