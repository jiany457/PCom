//Please copy&paste to your Arduino sketch

const int analogInPin = A0;

int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the sensor value from the analog input pin
  sensorValue = analogRead(analogInPin);

  // write the sensor value to serial
  // DO NOT WRITE ANYTHING ELSE TO SERIAL
  // Processing is expecting to receive ONLY this number
  // if you send over other stuff (like a nicely descriptive string like "Analog reading ="),
  // Processing will get confused. It may try to interpret the string as if it were a number,
  // resulting in nonsense.
  Serial.println(sensorValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}


