//boolean mySet = false;

int red1 = 10;
int red2 = 11;
int red3 = 12;
int green = 13;

int button1 = 2;
int button2 = 3;
int button3 = 4;

int buttonState = 0;

int unlockStep;
 
void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

   unlockStep = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
   
   // button1 -> step 1;
  buttonState = digitalRead(button1);
  if (buttonState == HIGH && unlockStep == 0) {
    digitalWrite(red1,HIGH);
    
    unlockStep = 1;
    buttonState = digitalRead(button2);
      
      if (buttonState == HIGH && unlockStep == 1) {  
      digitalWrite(red2,HIGH);
      unlockStep = 2;
      buttonState = digitalRead(button3);
         if (buttonState == HIGH && unlockStep == 2) {
         digitalWrite(green,HIGH);
          unlockStep = 3;    
          }
          else{
          setup();
          } 
      }else{
          setup();
      } 
    }else{
      setup();
    }
    delay(1000); 
    digitalWrite(red1,LOW);
    digitalWrite(red2,LOW);
    digitalWrite(green,LOW);
    
} 
