//Please copy&paste in Processing

import processing.serial.*;

Serial myPort;
int serialVal = 0;

void setup() {
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port that matches the name of your Arduino port
  // Find the name of your Arduino port in Arduino IDE Tools --> Port
  // Hint: In the line below, change which port you are selecting by
  // changing the 0 to other numbers to refer to other points in the list
  myPort = new Serial(this, Serial.list()[3], 9600);
  
  // sets the size of the canvas
  size(800,800);
  // sets the background color of the canvas in red, green, blue components
  background(40,40,40);
  // sets the framerate at which to update the animations on the canvas
  frameRate(10);

}

void draw() {
 // make the canvas blank again
 background(40, 40, 40);

 // draw a white ball whose size is determined by the value from serial
 fill(255, 255, 255);
 ellipse(400,400,serialVal,serialVal);
}



// READING THE SERIAL MESSAGES FROM ARDUINO

// this "buffer" stores the incoming serial message
String buf="";
// the "carriage return" ASCII code marks the end of a message
int cr = 13; // ASCII return == 13
// the "linefeed" ASCII code marks the end of a message
int lf = 10; // ASCII linefeed == 10

// called whenever serial data arrives
void serialEvent(Serial p) {
  // store the latest piece of the serial message
  int c = myPort.read();
  
  // if it is not the end of a message
  if (c != lf && c != cr) {
    // then keep adding to buffer
    buf += char(c);
  }
  // if it is the end of a message
  if (c == lf) {
    // convert the buffer into an integer value
    serialVal = int(buf);
    // print it out
    println("val="+serialVal); 
    // empty out the buffer so that we are ready to
    // receive new messages
    buf = ""; 
  }
}