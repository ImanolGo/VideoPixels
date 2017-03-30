/*
  SD Video Player
   
 Description:
 * Led video player reading content from SD Card 

 Hardware:
* Teensy 3.5
* WS2811 5V LED strips
   
 The circuit:
  * SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila, pin 7 on Teensy with audio board
 ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
 ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila, pin 14 on Teensy with audio board
 ** CS - depends on your SD card shield or module - pin 10 on Teensy with audio board
    Pin 4 used here for consistency with other Arduino examples

* LED Ground: Connected to GND
* LED +5V:: Connected to VSUB
* LED Data: Connected to pin 2

 
 created 30 March 2017
 by Imanol Gómez
 
 */
 // include the SD library:
#include <SD.h>
#include <SPI.h>
#define FILENAME    "10.BMP"
#define serialDebug 0        //whether or not to output whats read


 // include Fast LED Library
#include "FastLED.h"

// set up variables using the FastLED utility library functions:
#define FRAMES_PER_SECOND  24
#define DATA_PIN    2
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    596
CRGB leds[NUM_LEDS];
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


//set up files variables
File myFile;
long height = 1;
long bitmapOffset = 0x36;
long filePosition = 0;
int currentFrame = 0;

// Teensy 3.5 & 3.6 on-board: BUILTIN_SDCARD

const int chipSelect = BUILTIN_SDCARD;    

void setup()
{
  setupSerial();
  setupSD();
  setupLeds();
}


void setupSerial() {
  
  //Initialize serial
  Serial.begin(9600);
  delay(2000);
  
}

void setupSD() {


  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  loadBMPinfo(FILENAME);
  
}

void setupLeds() {
   // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps (5, 2400);
}
void loop(void) {
  updateLeds();
  
}

void updateLeds() 
{

  nextFrame();
  //rainbow();
  
   // send the 'leds' array out to the actual LED strip
  FastLED.show(); 
   
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 1 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  
}

void nextFrame() {
    currentFrame = (currentFrame + 1) % height;
    int index = height - currentFrame - 1;
    setFrame(index);
   
} 

void setFrame(int frameIndex) {

  if(frameIndex < 0 || frameIndex >= height){
    return;
  }
  
   filePosition = bitmapOffset+ (frameIndex *(NUM_LEDS * 3) );
   myFile.seek(filePosition);//get to data
   memset(leds, 0, NUM_LEDS * 3);//blank the array
  
    //something went wrong, myFile should not return -1 here.
      if (!myFile){ 
          Serial.println("the card broke"); 
          return;
      }
      
      //read an entire line to leds[]
      for(int i=0; i < NUM_LEDS; i++) {
          leds[i].b=myFile.read();
          leds[i].g=myFile.read();
          leds[i].r=myFile.read();   
                 
          if (serialDebug) {
            Serial.print(leds[i].r,HEX);  
            Serial.print(":");
            Serial.print(leds[i].g,HEX);  
            Serial.print(":");
            Serial.print(leds[i].b,HEX);  
            Serial.print(",");
          }
          
      }  
  
      FastLED.show(); //fastspi output
}


void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void loadBMPinfo(String fileName) {

    byte heightByte[4]; 
    height = 0; //start with a zero'd signed long, 4 bytes.
    
    if (SD.exists(FILENAME)) {
      Serial.print(FILENAME);
      Serial.println(" exists.");
    }
    else {
      Serial.print(FILENAME);
      Serial.println(" doesn't exist.");
    }


    myFile.close();  
    myFile = SD.open(FILENAME, FILE_READ);
    myFile.seek(0x16); //goto start byte of bitmap height 
    
    for (int i = 0; i < 4; i++){  //height is a 4 byte integer stored in reverse byte order
      heightByte[i] = myFile.read();
    } //end for grab
    
    for (int i = 3; i > 0; i--){ //3 2 1 not zero
      height = height | heightByte[i]; //add the i'th byte
      height = height << 8;            //bitshift everything 1 byte left
    }
    height = height | heightByte[0]; 
    myFile.seek(0xA);
    bitmapOffset = myFile.read();
    
    Serial.print("BitmapOffset:");   //debug if the bitmap data offset is correct
    Serial.println(bitmapOffset,HEX);
    Serial.print("Height:");
    Serial.println(height);
} 
