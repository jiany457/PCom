


//Ultra
const int trigPin = 13;
const int echoPin = 12;
long duration, cm;
float current_time=0;
float thousand = 1000;

//LED strip
int strip = 6;

int stage =0;


void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
//pinMode(6, OUTPUT);
//digitalWrite(6,LOW);
//pinMode(3, OUTPUT);
//digitalWrite(3,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonic();
 
   
}

void ultrasonic(){
   pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

current_time = millis();
cm = microsecondsToCentimeters(duration);  
 if(cm<=5){
    digitalWrite(6,HIGH);
//    digitalWrite(3,HIGH); 
  
//    stage = 1;
    } else{
      digitalWrite(6,LOW);
      }  
//if(stage =1){
//    digitalWrite(6,HIGH); 
////    digitalWrite(3,HIGH); 
   
 
  delay(100);

     Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  }

  long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

