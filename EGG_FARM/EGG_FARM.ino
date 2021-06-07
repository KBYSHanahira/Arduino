#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>>
#define BLYNK_PRINT Serial
char auth[] = "b4c0db913bea488fac35c55e1a9c0026";
char ssid[] = "microlab";
char pass[] = "20182019";

float h;
float t;

int LightStatus = 0;
float Average = 25;
float Histerresis = 1;


int Mode = 0;
int Modes = 0;
unsigned long previousMillis = 0;

#define DelayPin D7

void setup() {
Serial.begin(9600);
pinMode(DelayPin,OUTPUT);

Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);

dht.begin();

Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();
delay(1000);

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

void loop() {
  t = dht.readTemperature();
  h = dht.readHumidity();
  
  if(Mode == 0){
    TempMode();
  }
  if(Mode == 1){
    SettingMode();
  }
  
  unsigned long currentMillis = millis();
  if (digitalRead(D5)==0){
    previousMillis = currentMillis;
    while (digitalRead(D5)==0){
      currentMillis = millis();       
      delay(100);
      if (currentMillis - previousMillis >= 3000){
        if(Mode == 0){
          Mode = 1;
          SettingMode();
        }else if(Mode == 1){
          Mode = 0;
          TempMode();
        }
        while (digitalRead(D5)==0){
          delay(10);
        }
     }
   }
 }
  
}

void TempMode(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("  Smart Farm System");
  display.setCursor(0, 25);
  display.print("Temp = ");
  display.println(t);
  display.setCursor(0, 50);
  if(LightStatus == 0){
  display.print("Light = ");
  display.println("OFF");
  display.display();
  }else if(LightStatus == 1){
  display.print("Light = ");
  display.println("ON");
  display.display();
  }
  delay(200);
  Blynk.run();
  HisterresisStatus();
  SendDHT();
}

void SendDHT(){
  t = dht.readTemperature();
  Blynk.virtualWrite(V1, t);
  h = dht.readHumidity();
  Blynk.virtualWrite(V2, h);
}

void HisterresisStatus(){
  if(t >= ( Average + Histerresis)){
    digitalWrite(DelayPin,HIGH);
    LightStatus = 1;
    Blynk.virtualWrite(V3,LightStatus);
  }else if(t <= (Average - Histerresis)){
    digitalWrite(DelayPin,LOW);
    LightStatus = 0;
    Blynk.virtualWrite(V3,LightStatus);
  }
}
