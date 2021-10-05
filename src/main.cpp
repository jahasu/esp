#include <Arduino.h>
#include <FastLED.h>
#include <TMCStepper.h>
#include <BleKeyboard.h>
#include "FastLED_RGBW.h"


//tmc stepper 
#define EN_PIN    7  
#define DIR_PIN   6 
#define STEP_PIN  5  
#define CS_PIN    8  
#define SW_MOSI  9
#define SW_MISO 10
#define SW_SCK  11

#define R_SENSE 0.11f 

TMC2130Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

//button pin setup
#define buttonR 18
#define redCH 0
#define buttonG 19
#define greenCH 1
#define buttonB 21
#define blueCH 2
#define buttonInput 2

#define freq 5000
#define resolution 8

bool buttonPressed = false;
//neopixel setup
#define NUM_LEDS 100
#define DATA_PIN 6
//Bluetooth Control Setup
BleKeyboard bleKeyboard;


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int buttonBrightnessR = 0;
int fadeAmount = 2;

static uint8_t hue = 180;
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];
uint8_t abrightness = 0;
const uint8_t brightness = 255;


//stepper setup








void setup() {
//serial
Serial.begin(115200); 

//LED strip
FastLED.addLeds<WS2812B, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
FastLED.setBrightness(brightness);
FastLED.show();

//button and LEDs
pinMode(buttonPin,INPUT_PULLUP);

ledcSetup(redCH, freq, resolution);
ledcSetup(blueCH, freq, resolution);
ledcSetup(greenCH, freq, resolution);
ledcAttachPin(buttonR,redCH);
ledcAttachPin(buttonG,greenCH);
ledcAttachPin(buttonB,blueCH);

//steppers

//bluetooth
bleKeyboard.begin();


runmain();
}

void setRGB(int colour){
  ledcWrite(redCH, 255);
}
  

void buttonPulse(){


}
void lightWave(){

}
int lidMove(int lidDir){
  return 1;
}
int iPadMove(int ipadDir){
  return 1;
}





void runmain(){
  while(digitalRead(buttonInput)== 1){
    buttonPulse();

  }
  
  lightWave();
  lidMove(1); // 1 is open, 0 is closed  returns 1 if successful - will may need error catching LIMIT SWITCH?
  iPadMove(1);
  delay(1000);
  ipadMove(0);
  lidMove(0);




}



void loop() {
  //nothing to put here?
}

//free rtos stall detection??!!