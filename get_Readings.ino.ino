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
float tempVal; // Variable to store temperature value
float humidVal; // Variable to store humidity value
int smokeDPin = 3; // The digital pin for the smoke sensor
int LEDPin = 4; // The pin for LED

void setup() {
  // put your setup code here, to run once:
  //Give dht and smoke sensor readings a place to be read.
  Serial.begin(9600);
  pinMode(13, OUTPUT); //For LED indication of the threshold LED
  pinMode (smokeDPin, INPUT); //For digital output from smoke sens
  pinMode(LEDPin, OUTPUT); // LED for when a threshold is reached
  
}

void loop() {
  // put your main code here, to run repeatedly:
  smokeSensorVal = analogRead(A3); // Get the CO2 ppm value
  smokeDigitalVal = digitalRead(2); // Get digital value
  tempVal = dht.getTemperature(); // Get temperature read from dht
  humidVal = dht.getHumidity(); // Get humidity % from dht

  Serial.print("Temperature = "); 
  Serial.print(tempVal); // Output temp to Serial monitor
  Serial.println(" degrees Celcius");
  Serial.print("Humidity = ");
  Serial.print(humidVal); // The same with humidity
  Serial.println("%");
  Serial.print("CO2 PPM = ");
  Serial.println(smokeSensorVal); // The same with C02 PPM
  Serial.print("Digital Val: ");
  Serial.println(smokeDigitalVal); // The same with digital value of smoke sensor

  // Testing gas concentration. 0 if out of bounds, 1 if within threshold. Turns on LED on sensor
  if (smokeDigitalVal == LOW)
   {
    digitalWrite(13, HIGH); // Turn on the LED
  } 
  else
   {
    digitalWrite(13, LOW); // Turn off the LED
  }

  // Changes the brightness depending on severity of fire danger
  /*if (smokeSensorVal > 230 && tempVal > 23) {
    analogWrite(LEDPin, 255);
  }
  else*/ if (smokeSensorVal > 230 || tempVal > 23) {
    digitalWrite(LEDPin, HIGH);
  }
  else{
    digitalWrite(LEDPin, LOW);
  }
  delay(2000);
  /*
  digitalWrite(LEDPin, HIGH);
  delay(1000);
  digitalWrite(LEDPin, 100);
  delay(1000);
  digitalWrite(LEDPin, LOW);
  delay(500);*/

}
