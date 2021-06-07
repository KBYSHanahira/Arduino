#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#include <Adafruit_NeoPixel.h>
#define PIN            10
#define NUMPIXELS      2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
int loli;

SoftwareSerial Board1 (14, 12, false, 256);

void setup() {
  Serial.begin(9600);
  Board1.begin(9600);
  pixels.begin();
}

void loop() {
  t = dht.readTemperature();
  h = dht.readHumidity();
  Serial.print("Temp :");
  Serial.println(t);
  Board1.write("Temp :");
  Board1.write(t);
  delay(1000);

  while (Board1.available() > 0) {
    loli = Board1.read();
  }
  if(loli == 1){
    pixels.setPixelColor(1, pixels.Color(150,0,0));
    pixels.setPixelColor(0, pixels.Color(150,0,0));
    pixels.show();
  }
  if(loli == 2){
    pixels.setPixelColor(1, pixels.Color(0,150,0));
    pixels.setPixelColor(0, pixels.Color(0,150,0));
    pixels.show();
  }
  if(loli == 3){
    pixels.setPixelColor(1, pixels.Color(0,0,150));
    pixels.setPixelColor(0, pixels.Color(0,0,150));
    pixels.show();
  }
  if(loli == 4){
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
  }
}
