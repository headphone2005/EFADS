int sensorValue; // Variable to store analog sensor value
int digitalValue; // Variable to store digital sensor value
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  pinMode(13, OUTPUT); // Set pin 13 as an output (for LED indication)
  pinMode(3, INPUT); // Set pin 3 as an input (for digital output from the sensor)
}

void loop()
 {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(A3);

  // Read digital value from the sensor
  digitalValue = digitalRead(2);

  // Print sensor values to the serial monitor
  Serial.print("Analog Value: ");
  Serial.println(sensorValue);
  Serial.print("Digital Value: ");
  Serial.println(digitalValue);

  // If gas concentration exceeds a threshold, turn on an LED (connected to pin 13)
  if (digitalValue == LOW)
   {
    digitalWrite(13, HIGH); // Turn on the LED
  } 
  else
   {
    digitalWrite(13, LOW); // Turn off the LED
  }

  delay(1000); // Delay for 1 second before reading again
}
