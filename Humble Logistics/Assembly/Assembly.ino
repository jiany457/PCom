
//for ultrasonic
const int buttonPin = 2;     
const int ledPin =  4;      
const int trigPin = 13;     
const int echoPin =12; 
const int uvPin =  3;  

//UltraCalculation
long duration, cm;
float current_time=0;
float thousand = 1000;

//For motor              
int motorPin = 8;

//Button
int buttonState = 0;         // variable for reading the pushbutton status
int stage;              // variable for switching on and off the led and start and stop the measurements

  
void setup() {
   Serial.begin(9600);
   // LED
   pinMode(4, OUTPUT);
   pinMode(3, OUTPUT);
   
   digitalWrite(4, LOW);
   digitalWrite(3, LOW);
   //Button
   pinMode(2, INPUT);


 int stage = 0; 
    
}

void loop() {

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && stage == 0) { //BUTTON ON
    ultrasonic(); 
    delay(1000);
    stage = 1;
    }else if(buttonState == HIGH && stage == 1){    
    delay(1000);
    digitalWrite(13, LOW); //turn off ultra
    digitalWrite(8,HIGH);//motor ofF
     stage = 0;  
    }
  if (buttonState == LOW && stage == 1){ 
      ultrasonic(); // turn on ultra 
      motor(); //motor on  
//      digitalWrite(3, HIGH); 
      digitalWrite(4, HIGH);
        
        if (cm <=5){
//            digitalWrite(4, HIGH);
            digitalWrite(8, HIGH); 
            stage = 2;//MOTOR OFF
          } 
  }
  
  if(stage == 2){
    digitalWrite(8,HIGH);//motor off
    digitalWrite(3, HIGH); 
    stage = 0;
  }
  
}

void motor(){
    pinMode(8, OUTPUT); 
    digitalWrite(8, LOW); 
  }

void ultrasonic(){
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(12, HIGH); 
  current_time = millis();
  cm = microsecondsToCentimeters(duration); 
    
  
//  if (cm <=5){
//            digitalWrite(3, HIGH);
//            digitalWrite(8, HIGH); //MOTOR OFF
//          }else{
//            digitalWrite(3, LOW);
//          
//            }  

  Serial.print(current_time / thousand);
  Serial.print(" s, ");
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();

  delay(500);
  }


long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}




