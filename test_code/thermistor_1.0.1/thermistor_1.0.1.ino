#include "pins_energia.h"
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
