const int trigPin = 13; //naming a constant value / giving a variable name / #define acts as a find and replace
const int echoPin = 12;
#define ledPin 11


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); //trigPin is sending out the signal
  pinMode(echoPin, INPUT); //echoPin is retrieving information, therefore it is INPUT
  pinMode (ledPin, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1; //Time it took for the echo to be received and divided in half then divided by the speed of sound
  
  Serial.print(distance);
  Serial.println(" cm");
  delay(500); //delay half a second before repeating the loop

  map(distance, 0,1023,0,255);
  analogWrite(ledPin, distance);
}
