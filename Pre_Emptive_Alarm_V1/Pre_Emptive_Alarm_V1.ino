/*
Include the following libraries
DHT
- Digitial Humidity Temperature (DHT/dht)
LCD
- SPI
- Wire
- Adafruit_GFX
- Adafruit_SSD1306 (The model of LCD being utilized)

The following items are used
- Digital Humidty Temperature reader (DHT22)
- MQ-135 Gas Sensor
- 128x64 Liquid Crystal Display(LCD)
- FBS50D Speaker (0.5 W, 8 Ohm)

*/
#include <DHT22.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
const int Screen_Address = 0x3C; // The I2c address for the LCD (Is subject to change! Scan EVERYTIME!)
const int Screen_Width = 128; // Set the width (x limit) of LCD
const int Screen_Height = 64; // Set the height (y limit) of LCD
const int OLED_Reset = -1; // The reset pin number (-1 since it shares Arduino's reset pin)
// Create object for DHT
DHT22 dht(dhtPin);
// Create object for LCD
Adafruit_SSD1306 display(Screen_Width, Screen_Height, &Wire, OLED_Reset);

void setup() {
  // put your setup code here, to run once:
  // Give dht and smoke sensor readings a place to be read.
  Serial.begin(9600);
  pinMode(13, OUTPUT); // For LED indication of the threshold LED
  pinMode (smokeDPin, INPUT); // For digital output from smoke sensor
  pinMode(speakerPin, OUTPUT); // Speaker signal for when hazardous conditions are met
  display.clearDisplay();
  //printWarning();
  //display.display();
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

// If any fire hazard conditions met, the LCD will print a warning
void printWarning() {
  int16_t i; 
  display.fillScreen(SSD1306_WHITE); // Clear the display buffer (Currently filling screen for testing)
  /*display.println("WARNING!");
  delay(2000);
  display.println("CONDITIONS HAZARDOUS");*/
}

// If the conditions for a fire are not met, the LCD may go blank
void idle() {

  display.clearDisplay();

}
