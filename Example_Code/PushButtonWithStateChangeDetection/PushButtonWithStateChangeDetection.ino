/*
  DigitalReadSerial with on-board Pushbutton
  Reads a digital input on pin 5, prints the result to the serial monitor 

// CHANGES:  
// Instead of using delays, we will use state change detection to debounce the switch.
// Hence, action takes place only when a change in the switch's state is detected.
// This is a lot more accurate than timing delays.
// All operations will have to take place within this "if loop" for the state change.
// The changes made here are based on the built-in example called StateChangeDetection.
  
// This code demonstrates that a 0 is printed in the serial monitor only when PUSH2 is pressed,
// otherwise nothing is printed to the monitor.
// This code also demonstrates the use of "if" statements.
   
  Harware Required:
  * MSP-EXP430G2 LaunchPad
  
  This example code is in the public domain.
 */

// digital pin 5 has a pushbutton attached to it. Give it a name:
int pushButton = 5;

int LED1 = P1_0;           // assign the red LED (P1.0) the variable name LED1.
int LED2 = P1_6;           // assign the green LED (P1.6) the variable name LED2.
int buttonState = 0;       // the current reading from the input pin.
int lastButtonState = 0;   // the previous reading from the input pin.

// the setup routine runs once when you press reset:
void setup() {
  // initialize the LEDs as an output:
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  // make the on-board pushbutton's pin an input pullup:
  // NOTE: Launchpad on-board button does not support INPUT_PULLDOWN for PinMode(). 
  pinMode(pushButton, INPUT_PULLUP);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2553 must use 9600
}

// the loop routine runs over and over again forever:
void loop() {  
  // read the pushbutton input pin:
  buttonState = digitalRead(pushButton);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, then
    if (buttonState == LOW) {
      // if the current state is LOW then the button
      // went from open-circuit to close-circuit:
      // IF THE PUSH BUTTON IS PRESSED THEN PRINT BUTTON STATE,
      // TURN OFF RED LED AND TURN ON GREEN LED
       Serial.println(buttonState);
      // Turn off the red LED
      digitalWrite(LED1, LOW);
      // Turn on the green LED
      digitalWrite(LED2, HIGH);
    } 
      else {
        // the current state is HIGH and the button
        // went to open-circuit being its default state
        // PUSH BUTTON IS UNPRESSED SO PRINT BUTTON STATE,
        // TURN ON RED LED AND TURN OFF GREEN LED
        Serial.println(buttonState);
        // Turn on the red LED
        digitalWrite(LED1, HIGH); 
        // Turn off the green LED
        digitalWrite(LED2, LOW); 
      }
  } 
  // save the current state as the last state, 
  // for next time through the loop
  lastButtonState = buttonState; 
}
