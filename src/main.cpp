#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TMCStepper.h>
#include <BleKeyboard.h>
#include <math.h>



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
#define buttonR 33
#define redCH 3
#define buttonG 25
#define greenCH 1
#define buttonB 26
#define blueCH 2
#define buttonInput 14

#define freq 5000
#define resolution 8

bool buttonPressed = false;
//neopixel setup
#define NUMPIXELS 160
#define PIN        27

#define MATH_MIN_B 0
#define MATH_MAX_B 255
#define MATH_SPREAD 0.1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
//Bluetooth Control Setup
BleKeyboard bleKeyboard;


//stepper setup





void setRGB(int colour){
  ledcWrite(redCH, colour);
  ledcWrite(greenCH, colour);
  ledcWrite(blueCH, colour);
}
  
void buttonPulse(){
    
    int pulse_dir = 0;
    int pulse_i = 0;
    
    
    while(!digitalRead(buttonInput)){
    setRGB(pulse_i);
    if(pulse_i == 200 || pulse_i == 0){
      pulse_dir =!pulse_dir;
    }
    if (pulse_dir == 0){
      pulse_i--;
    }
    else{
      pulse_i++;
    }
    delay(5);

 
    

  }

}
void lightWave(){
   
   pixels.clear();

  Serial.println("light wave");
  int red_arr[NUMPIXELS*2];
  int blue_arr[NUMPIXELS*2];
  for(int i = 0; i< NUMPIXELS*2;i++){//gnerete array
  
  double b_x = i*0.09;

 double r_x = i*0.14;
  blue_arr[i]= ((MATH_MAX_B - MATH_MIN_B)* pow(sin(b_x),2.0))+MATH_MIN_B;
  red_arr[i]= ((MATH_MAX_B - MATH_MIN_B)* pow(sin(r_x),2.0))+MATH_MIN_B;

  }
  for(int i = 0; i<NUMPIXELS; i++){ //show array
    pixels.setPixelColor(i, red_arr[i], 0, blue_arr[i],0);
  }
  
  pixels.show();
  Serial.println("show array");
  delay(2000);

//move array
}
int lidMove(int lidDir){
  return 1;
}
int iPadMove(int ipadDir){
  return 1;
}






void runmain(){
  /*setRGB(0);
  delay(1000);
    
  buttonPulse();
 
  ledcWrite(redCH, 255);

  
  bleKeyboard.write(KEY_RETURN);
  delay(500);
  bleKeyboard.write(KEY_RETURN);
  delay(1000);
  bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  */
  lightWave();
  lidMove(1); // 1 is open, 0 is closed  returns 1 if successful - will may need error catching LIMIT SWITCH?
  iPadMove(1);
  delay(1000);
  iPadMove(0);
  lidMove(0);




}










void setup() {


//serial
Serial.begin(115200); 


//button and LEDs
pinMode(buttonInput,INPUT);

ledcSetup(redCH, freq, resolution);
ledcSetup(blueCH, freq, resolution);
ledcSetup(greenCH, freq, resolution);
ledcAttachPin(buttonR,redCH);
ledcAttachPin(buttonG,greenCH);
ledcAttachPin(buttonB,blueCH); 



//steppers

//bluetooth
bleKeyboard.begin();

//neopixels
pixels.begin();
pixels.show();
/*
while(!bleKeyboard.isConnected()) {
  ledcWrite(redCH, 255);
delay(100);
ledcWrite(redCH, 0);
delay(100);
}
*/
runmain();
}




void loop() {
  

  //nothing to put here?
}

//free rtos stall detection??!!