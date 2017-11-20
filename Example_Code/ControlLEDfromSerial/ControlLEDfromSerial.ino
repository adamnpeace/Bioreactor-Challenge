// Modified version of the following tutorial:
// http://energia.nu/Tutorial_ReadASCIIString.html

/* INSTRUCTIONS:
Once you have programmed the LaunchPad, open your Serial monitor.
Make sure you have chosen to send a newline character when sending a message.
Enter values between 0-255 for the lights.
Once you have sent the values to the Launchpad,
the attached LED will turn the color you specified, 
and you will receive the HEX values in the serial monitor. 
*/


// pins for the LEDs:
const int greenPin = 14;

void setup() {
 // initialize serial:
 Serial.begin(9600);
 // make the pins outputs:
 pinMode(greenPin, OUTPUT); 
}

void loop() {
// if there's any serial available, read it:
while (Serial.available() > 0) {

  // look for the next valid integer in the incoming serial stream:
  int green = Serial.parseInt(); 

  // look for the newline. That's the end of your
  // sentence:
  if (Serial.read() == '\n') {
  // constrain the values to 0 - 255 
  green = constrain(green, 0, 255);

  // fade the green LED: 
  analogWrite(greenPin, green);

  // print the three numbers in one string as hexadecimal:
  Serial.print(green, HEX);
  }
 }
}
