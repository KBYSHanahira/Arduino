#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1);
#define DHTPIN D4
#define BUTTON1 D0
#define BUTTON2 D3
#define LED D7
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
unsigned long previousMillis = 0;
const long interval = 2000;
int count = 25;
float h;
float t;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
 ///////////// MODE SETUP ///////////////////
void SetupTemp(){
  h = dht.readHumidity();
  t = dht.readTemperature();
  OLED.clearDisplay();
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  OLED.println("Setup Mode");
  OLED.println("Temp :");
  OLED.display(t);
  OLED.println("Humidity :");
  OLED.display(h);
  delay(2000);
  
}
//////////////// MODE START ///////////////////////
void BeginTemp(){
  h = dht.readHumidity();
  t = dht.readTemperature();
  OLED.clearDisplay();
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  OLED.println("Temp Mode");
  OLED.println("Temp :");
  OLED.display(t);
  OLED.println("Humidity :");
  OLED.display(h);
  delay(2000);
  
}
void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  if(BUTTON1 == LOW){
    count = count+1;
  }
  if(count >= 29){
    count = 25;
  }
  unsigned long currentMillis = millis();
  while(digitalRead(BUTTON2 == LOW)){
    if (currentMillis - previousMillis >= interval)
    previousMillis = currentMillis;
    SetupTemp();
  }
}
