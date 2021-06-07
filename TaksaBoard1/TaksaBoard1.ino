#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>
SoftwareSerial Board1(12,13);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

float h;
float t;
char Seria = '0';
char Mirai[2];
int i;

void setup() {
Serial.begin(9600);
Board1.begin(9600);
Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();
delay(2000);

dht.begin();

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

void loop() {
  t = dht.readTemperature();
  float temp = t;
  while (Serial.available() > 0) {
    Seria = Serial.read();
  }
  while (Board1.available() > 0) {
    Mirai[i] = Board1.read();
    i++;
    if(i > 2){
      i = 0;
    }
  }
  float LUX = Mirai[1];
  
  if(Mirai[0] == 'D'){
    display.clearDisplay();
    display.setCursor(0,25);
    display.print("   LUX :");
    display.println(LUX);
    display.display();
  }
  Serial.println(Mirai[1]);
  Board1.write(Seria);
  Board1.write(t);
  Board1.write(temp);
  Serial.println(Seria);
  Serial.print("Send DHT 22 :");
  Serial.println(t);
  delay(1000);
}
