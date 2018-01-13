#include <math.h>

// Heater
int THERMISTOR_PIN = A0;
int HEATER_PIN = 2;
double DESIRED_TEMP = 30;

// Motor
int RPM_PIN = 3;
int MOTOR_PIN = 6;
unsigned long startTime = 0;
float TARGET_RPM = 60;
float curRPM = 0;
int motorVoltage = 10;
int counter = 0;

// pH
int PH_PIN = A1;
int BASE_PIN = 4;
int ACID_PIN = 5;

float FARADAY = 96485.309;
float GAS_CONST = 8.314510;
int REF_PH = 7;
int OFFSET = 0.512;
int PUMP_VOLTAGE = 255;

float pH = 0.0;
float min_pH = 4.8;
float max_pH = 5.0;


// =================================== //
// ============== SETUP ============== //
// =================================== //
void setup() {
  Serial.begin(115200); //Set the Serial port at 9600 baud rate
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(THERMISTOR_PIN, INPUT);

  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(RPM_PIN, INPUT);

  pinMode(PH_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(RPM_PIN), upCount, RISING);
}

// =============== Heater
double getTemperature(int rawADC) {
  if (rawADC == 0) {
    return -300;
  }
  else {
    rawADC -= 10; //Modify the input value to calibrate the temperature.
    double temp;
    temp = log(((10240000 / rawADC) - 10000));
    temp = 1 / (0.001129148 +
                (0.000234125 + (0.0000000876741 * temp * temp )) * temp );
    return temp - 273.15; // Convert Kelvin to Celsius
  }

}

// =============== Motor
void calculateRPM() {
  // Divide by 2 because counter is half revs
  // Multiply by 30,000 to get RPM instead of millisecs
  curRPM = (4.0 / 7.0) * (((float)counter / 2.0) / (millis() - startTime)) * (1000.0 * 30.0);
  startTime = millis();
  counter = 0;
  Serial.print("RPM:");
  Serial.print(curRPM);
  Serial.print(",");
}
void updateMotorVoltage() {
  if (curRPM < TARGET_RPM)
    motorVoltage++;
  else if (curRPM > TARGET_RPM)
    motorVoltage--;
}
void upCount() {
  counter++;
}

// =============== pH
void checkPh() {
  int raw = analogRead(PH_PIN);
  float voltage = raw * (3.3 / 1023.0);
  pH = calcPh(0.177, 25 + 273.15);
    Serial.print("PH:");
    Serial.println(pH);
}
void adjustPh() {
  if (pH < min_pH)
    injectBase();
  else if (pH > max_pH)
    injectAcid();
}
void injectBase() {
  analogWrite(BASE_PIN, PUMP_VOLTAGE);
}
void injectAcid() {
  analogWrite(ACID_PIN, PUMP_VOLTAGE);
}
float calcPh(float voltage, float temperature) {
  return (float)REF_PH - ((voltage - (float)OFFSET) * FARADAY / (GAS_CONST * temperature * M_LN10));
}
// =================================== //
// =============== LOOP ============== //
// =================================== //
void loop() {
  
  int input;
  double temperature;

  //========Motor=========
  if (counter >= 20) {
    calculateRPM();
    updateMotorVoltage();
  }
  analogWrite(MOTOR_PIN, motorVoltage);
  
  //========Heater=========
  input = analogRead(THERMISTOR_PIN);
  temperature = getTemperature(input);
  Serial.print("TEM:");
  Serial.print(temperature);
  Serial.print(",");
  if (temperature < DESIRED_TEMP)
  {
    digitalWrite(HEATER_PIN, HIGH);
  }
  else
  {
    digitalWrite(HEATER_PIN, LOW);
  }

  

  //========PH========
  checkPh();
  adjustPh();

  delay(200);
}

