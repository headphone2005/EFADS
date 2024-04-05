/*
Include the Digitial Humidity Temperature (DHT/dht) library
Declare the pin being used for the dht sensor
Create a DHT object

*/
#include <DHT22.h>
int dhtPin = 7;
DHT22 dht(dhtPin);
int smokeSensorVal; // Variable to store analog sensor value
int smokeDigitalVal; // Variable to store digital sensor value


void setup() {
  // put your setup code here, to run once:
  //Give dht and smoke sensor readings a place to be read.
  Serial.begin(9600);
  pinMode(13, OUTPUT); //For LED indication
  pinMode (3, INPUT); //For digital output from smoke sens
  
}

void loop() {
  // put your main code here, to run repeatedly:
  smokeSensorVal = analogRead(A3); //Get the CO2 ppm value
  smokeDigitalVal = digitalRead(2); //Get digital value

  Serial.print("Temperature = "); 
  Serial.println(dht.getTemperature()); //Obtain the temperature read from the dht and output to serial monitor
  Serial.print("Humidity = ");
  Serial.println(dht.getHumidity()); //Do the same but with the humidity
  Serial.print("Smoke PPM = ");
  Serial.println(smokeSensorVal); //Print the CO2 PPM
  Serial.print("Digital Val: ");
  Serial.println(smokeDigitalVal); //Print the digital val. 1 if within threshold. 0 if not.
  delay(2000);

  // Testing gas concentration. 0 if out of bounds, 1 if within threshold. Turns on LED
  if (smokeDigitalVal == LOW)
   {
    digitalWrite(13, HIGH); // Turn on the LED
  } 
  else
   {
    digitalWrite(13, LOW); // Turn off the LED
  }

}
