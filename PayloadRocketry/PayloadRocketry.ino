// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
// Include the Servo library 
#include <Servo.h> 
 
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 5
#define fan 3
int servoPin = 6; 
// Create a servo object 
Servo Servo1; 
 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
int NumSensors=0;
/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  pinMode(fan, OUTPUT);
  digitalWrite(fan, HIGH);
  // start serial port
  Serial.begin(9600); 
  Serial.println("Dallas Temperature IC Control Library Demo");
  Servo1.attach(servoPin); 
  
 
  // Start up the library
  sensors.begin();
  NumSensors=sensors.getDeviceCount();
  Serial.print(NumSensors);Serial.print(" sensor");
  if((NumSensors>1)&(NumSensors!=0))
    Serial.print("s");
  Serial.println(" available");
}
 
/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  for(int i=0;i<NumSensors;i++)
  {
    Serial.print("Temperature Sensor ");Serial.print(i);Serial.print(" : ");
    float sensorTemp = sensors.getTempCByIndex(i);
    Serial.print(sensorTemp);
    Serial.print(" Celcius");
    if(sensorTemp > 30)
      {
        Servo1.write(0); 
        delay(1000);
        Servo1.write(90); 
        delay(1000);
      }
    if(i<NumSensors-1)
      Serial.print(",");
  }  
  delay(3000);
  Serial.println();
}
