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
int pitch = 2000; // Pitch level of speaker. Starting at 2000(Hz)
// Required Pins
const int smokeDPin = 2; // The digital pin for the smoke sensor
const int smokeAPin = A3; // The analog pin for the smoke sensor
const int speakerPin = 4; // The pin for LED (Will be converted into speaker pin)

void setup() {
  // put your setup code here, to run once:
  //Give dht and smoke sensor readings a place to be read.
  Serial.begin(9600);
  pinMode(13, OUTPUT); //For LED indication of the threshold LED
  pinMode (smokeDPin, INPUT); //For digital output from smoke sens
  pinMode(speakerPin, OUTPUT); // LED for when a threshold is reached
  
}

void loop() {
  // put your main code here, to run repeatedly:
  smokeSensorVal = analogRead(smokeAPin); // Get the CO2 ppm value
  smokeDigitalVal = digitalRead(smokeDPin); // Get digital value
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

  if (smokeSensorVal > 230 && tempVal > 23) {
    for (int i = 0; i < 6; i++) {
      tone(speakerPin, pitch, 150);
      delay(150);
    }
  }
  else if (smokeSensorVal > 230 || tempVal > 23) {
    // digitalWrite(LEDPin, HIGH); // Testing value readings
    for (int j = 0; j < 3; j++) {
    tone(speakerPin, pitch, 500);
      delay(500);
    }
  }

  else{
    // digitalWrite(LEDPin, LOW); // Testing value readings
  }
  delay(1000);
  /*
  digitalWrite(LEDPin, HIGH);
  delay(1000);
  digitalWrite(LEDPin, 100);
  delay(1000);
  digitalWrite(LEDPin, LOW);
  delay(500);*/

}
