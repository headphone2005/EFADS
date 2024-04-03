/*
Include the Digitial Humidity Temperature (DHT/dht) library
Declare the pin being used for the dht sensor
Create a DHT object

*/
#include <DHT22.h>
int dhtPin = 2;
DHT22 dht(dhtPin);


void setup() {
  // put your setup code here, to run once:
  //Give dht readings a place to be read.
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("\nTemperature = "); 
  Serial.print(dht.getTemperature()); //Obtain the temperature read from the dht and output to serial monitor
  Serial.print("\nHumidity = ");
  Serial.print(dht.getHumidity()); //Do the same but with the humidity
  delay(2000);

}
