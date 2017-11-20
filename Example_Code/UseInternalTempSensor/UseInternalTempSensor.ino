// Tutorial available at:
// http://msp430launchpad.weebly.com/tutorial-6.html

// MSP430 overview:
// http://archive.cnx.org/contents/84f35a80-b08e-4223-bdce-212f6d22f386@3/overview-of-the-msp430-microcontroller-from-texas-instruments

void setup()
{
  analogReference(INTERNAL1V5);
  Serial.begin(9600);  
}

void loop()
{
  long sensorValue = analogRead(A10)-630;
  long fValue = (sensorValue * 761)/1024;
  float cValue = (fValue - 32.0) / 1.8;
  Serial.print(fValue,DEC);
  Serial.write('*');
  Serial.println("F");
  Serial.print(cValue,DEC);
  Serial.write('*');
  Serial.println("C");
  delay(500);
  
}
