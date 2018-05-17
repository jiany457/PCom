#include <Stepper.h>
#include <Wire.h>
#include "Adafruit_Trellis.h"

//Ultra
const int trigPin = 3;     
const int echoPin =2; 
long duration, cm;
float current_time=0;
float thousand = 1000;


//Trellis
#define MOMENTARY 0
#define LATCHING 1 // lock
// set the mode here
#define MODE LATCHING //lock mode
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)
#define INTPIN A2


//motor
int oneway;
int onerev = 6400;
int microSecDelay = 100;
int dirPin = 8;
int stepPin = 9;

//LED
int red = 13;
int green = 12;
int strip = 6;

int stage;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Trellis Demo");
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, LOW);
  trellis.begin(0x70);

//Turn on all LED at beginning
//  for (uint8_t i=0; i<numKeys; i++) { //numKeys = 16
//    trellis.setLED(i);
//    trellis.clrLED(6);
//    trellis.clrLED(8);
//    trellis.clrLED(1);
//    trellis.writeDisplay();    
//    delay(50);
//  }
//
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }

    //NEMA
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);
    oneway = 1;

  //LED
  pinMode (12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(6, OUTPUT);
    digitalWrite(6,HIGH);


  stage = 0;
}

void loop() {
ultrasonic();
  
  delay(50);
  trellisMode();
  digitalWrite(13,LOW);
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
}


void trellisMode(){
  
if (MODE == MOMENTARY) {
    
    if (trellis.readSwitches())// If a button was just pressed or released... //to check is the buttonstate is changed or not, false/true
    {  
      for (uint8_t i=0; i<numKeys; i++)      // go through every button
      {
        if (trellis.justPressed(i)) // if it was pressed, turn it on
        {
//            Serial.print("v"); Serial.println(i);
            trellis.setLED(i);            
        }  
          if (trellis.justReleased(i)) // if it was released, turn it off
        {  
//            Serial.print("^"); Serial.println(i);
            trellis.clrLED(i);
        }    
      }
      trellis.writeDisplay();
   }
   
 }

  if (MODE == LATCHING) {
    
    if (trellis.readSwitches()) {    
      for (uint8_t i=0; i<numKeys; i++)      
      { 
          if (trellis.justPressed(6)&&trellis.justPressed(8)&&trellis.justPressed(1))   
          { 
//            Serial.print("v"); Serial.println(i);
            digitalWrite(12,HIGH);  
            delay(500);    
            NEMA();
            stage = 1;
                   
            if (trellis.isLED(i)) // Alternate the LED       
            trellis.clrLED(i);          
             else
              trellis.setLED(i);
              
          }else{
            digitalWrite(13,HIGH);
            digitalWrite(stepPin, LOW);
            }
      }
   
      trellis.writeDisplay();
    }
  }

  if(stage == 1){
    NEMA();
//    digitalWrite(stepPin, HIGH);
  }
}

void NEMA(){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(microSecDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(microSecDelay);
    oneway+=0;
  }

  void ultrasonic(){
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(10);
  digitalWrite(3, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(2, HIGH); 
  current_time = millis();
  cm = microsecondsToCentimeters(duration);
    delay(500);  

      if(cm <= 5){
      delay(30); 
  //Turn on all LED at beginning
  for (uint8_t i=0; i<numKeys; i++) { //numKeys = 16
    trellis.setLED(i);
    trellis.clrLED(6);
    trellis.clrLED(8);
    trellis.clrLED(1);
    trellis.writeDisplay(); 
  }
    digitalWrite(6,LOW);   
  }
  }

  

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}



