/*
Include the following libraries
DHT
- Digitial Humidity Temperature (DHT/dht)

The following items are used
- Digital Humidty Temperature reader (DHT22)
- MQ-135 Gas Sensor
- 2 LEDs (Of any color)
- HLO3400-2 AMCON (2 W, 8 Ohm)

*/
#include <DHT22.h> 


int smokeSensorVal; // Variable to store analog sensor value (CO2 PPM)
int smokeDigitalVal; // Variable to store digital sensor value (If values are accurate/trustable)
float tempVal; // Variable to store temperature value (In degrees Celcius)
float humidVal; // Variable to store humidity value (In percentile)
int pitch = 2000; // Pitch level of speaker. Starting at 2000(Hz)
// Required Pins
const int dhtPin = 7; // The pin for the DHT.
const int smokeDPin = 2; // The digital pin for the smoke sensor
const int smokeAPin = A3; // The analog pin for the smoke sensor
const int speakerPin = 4; // The pin for the speaker
const int ledPinOne = 11; // The pin for the first LED
const int ledPinTwo = 10; // The pin for the second LED
// Create object for DHT
DHT22 dht(dhtPin);

void setup() {
  // put your setup code here, to run once:
  // Give dht and smoke sensor readings a place to be read.
  Serial.begin(9600);
  pinMode(13, OUTPUT); // For LED indication of the threshold LED
  pinMode (smokeDPin, INPUT); // For digital output from smoke sensor
  pinMode(speakerPin, OUTPUT); // Speaker signal for when hazardous conditions are met
  pinMode(ledPinOne, OUTPUT); // Setting LED pin so it can give off light
  pinMode(ledPinTwo, OUTPUT); // Same as above
}

void loop() {
  // put your main code here, to run repeatedly:
  smokeSensorVal = analogRead(smokeAPin); // Get the CO2 PPM level
  smokeDigitalVal = digitalRead(smokeDPin); // Get bounds value
  tempVal = dht.getTemperature(); // Get temperature read from dht
  humidVal = dht.getHumidity(); // Get humidity % from dht

  Serial.print("Temperature = "); 
  Serial.print(tempVal); // Output temperature to Serial monitor
  Serial.println(" degrees Celcius");
  Serial.print("Humidity = ");
  Serial.print(humidVal); // The same with humidity
  Serial.println("%");
  Serial.print("CO2 PPM = ");
  Serial.println(smokeSensorVal); // The same with CO2 PPM
  Serial.print("Digital Val: ");
  Serial.println(smokeDigitalVal); // The same with digital value of smoke sensor

  // Testing gas concentration. 0 if out of bounds, 1 if within threshold. Handles Smoke Sensor LED
  if (smokeDigitalVal == LOW)
   {
    digitalWrite(13, HIGH); // Turn on the LED
  } 
  else
   {
    digitalWrite(13, LOW); // Turn off the LED
  }

  // If both temperature and CO2 threshold are met, the following runs. 
  if (smokeSensorVal > 230 && tempVal > 23.0) {
    // Quickly and repeatedly causes the speaker to make noise at twice the set pitch
    // Also flickers both LEDs in this given time
    for (int i = 0; i < 6; i++) {
      tone(speakerPin, pitch*2, 150);
      digitalWrite(ledPinOne, HIGH);
      digitalWrite(ledPinTwo, HIGH);
      delay(150);
      digitalWrite(ledPinOne, LOW);
      digitalWrite(ledPinTwo, LOW);

    }
  }
  // If only one of the following conditions were met, the following runs.
  else if (smokeSensorVal > 230 || tempVal > 23.0) {
    // digitalWrite(LEDPin, HIGH); // Testing value readings
    // Slowly beeps the the speaker at the set pitch
    // Also flickers only one LED
    for (int j = 0; j < 3; j++) {
      tone(speakerPin, pitch, 500);
      digitalWrite(ledPinOne, HIGH);
      delay(500);
      digitalWrite(ledPinOne, LOW);

    }
  }

  //If no hazardous conditions are met, turn off all warnings
  else{
    // digitalWrite(LEDPin, LOW); // Testing value readings
    digitalWrite(ledPinOne, LOW);
    digitalWrite(ledPinTwo, LOW);
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

