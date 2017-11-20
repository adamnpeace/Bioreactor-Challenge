/*
  Example 09: Temperature (Thermistor and Temp Sensor)
  Sidekick Basic Kit for TI LaunchPad
  
  In this example we are going to compare the results of a thermistor
  and an Analog Temperature Sensor. A thermistor is a very basic way
  to get temperature data. It is a simple device that changes its 
  resistance based on temperature. For more accuracy, you can use an analog 
  temperature sensor like the LM19 but there are many different types
  of temperature sensors available.
  
  Here we will build a simple circuit with both sensors and then read
  the values from the Energia Serial Monitor.
  
  Hardware Required:
  * TI LaunchPad
  * Breadboard BoosterPack
  * Breadboard
  * Thermistor
  * LM19 Temperature Sensor
  * 10K resistor (optional)
  * 6x Jumper Wires
  
  The LM19 Example is by Kerry Wong
  http://www.kerrywong.com/2010/05/09/working-with-lm19-temperature-sensor/
  Modified by Mark Easley
  
  This example code is in the public domain.
*/

// For the Thermistor: Attach VCC to left leg, an AnalogRead capable pin (2) to right leg  
// with a 10K resistor to GND in series. 
// For the Temp Sensor: Attach VCC to the left leg, an AnalogRead capable pin (6) to the 
// middle leg, and GND to the right leg. The letters and flat face should be facing you.  
// Check the datasheet if you want to verify the correct pin connections. 
// This example uses pin 2 and 6 on your LaunchPad, but can be changed to any analog pin.
// WARNING: the LM19 will get very hot to the touch if you have it plugged in backwards!

/* In the setup function we will initialize the Serial library
 * which let's us send and receive data over the UART channel
 */
void setup()
{
  // initialize serial communication over UART at 9600 baud
  Serial.begin(9600); 
}

/* In the loop section we will take measurements from our two sensors
 * perform any mathematical formulas to convert to the temperature,
 * and then print out the information to the console (serial monitor).
 */
void loop()
{
  // >>> Thermistor Section <<<
  // take in analog data from thermistor and run it through formulas 
  // and conversions
  
  float ThermistorVal = analogRead(2);
  float ThermistorTempC;
  float ThermistorTempF;
 
  ThermistorTempC = logf(10000.0 * ((1024.0 / ThermistorVal - 1)));
  //         = logf(10000.0 / (1024.0 / ThermistorVal - 1)); // for pull-up configuration
  ThermistorTempC = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * ThermistorTempC 
                    * ThermistorTempC ))* ThermistorTempC );
  ThermistorTempC = ThermistorTempC - 273.15;            // Convert Kelvin to Celcius
  ThermistorTempF = (ThermistorTempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  Serial.print("Thermistor: ");
  Serial.print("vin=");
  Serial.print(ThermistorVal);
  Serial.print(" ");
  Serial.print("TempC=");
  Serial.print(ThermistorTempC);
  Serial.print("  ");
  Serial.print("TempF=");
  Serial.print(ThermistorTempF);
  Serial.println();

  
  // >>> End of Thermistor Section <<<
  
  
}
