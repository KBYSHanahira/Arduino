#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;
int relayPin = 13;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  pinMode(relayPin, OUTPUT);
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.println(lux);
  delay(1000);
  if(lux >= 600){
  digitalWrite(relayPin,LOW);
  }else{
   digitalWrite(relayPin,HIGH); 
  }
}
 
