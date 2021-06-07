#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1);

#define BUTTON1 D7
#define BUTTON2 D6
#define LED D0

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
int Mode = 0;
bool sw,sw2 = true;
const long interval = 3000;
unsigned long previousMillis = 0;
int Count = 25;

void setup() {
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  t = dht.readTemperature();
  h = dht.readHumidity();
  Serial.print("Temp :");
  Serial.println(t);
  Serial.print("Humidity :");
  Serial.println(h);
  sw = digitalRead(BUTTON1);
  sw2 = digitalRead(BUTTON2);
  Serial.print("Mode =");
  Serial.println(Mode);
  Serial.print("Status =");
  Serial.println(sw);
  if(digitalRead(BUTTON1)== 0){
    tone(D8,2000,100);
  }
  if(digitalRead(BUTTON2)== 0){
    tone(D8,2000,100);
  }
  if(Mode == 0){
    TempMode();
  }
  if(Mode == 1){
    SettingMode();
  }
  if(t >= Count){
  digitalWrite(LED,HIGH);
  }else{
    digitalWrite(LED,LOW);
  }
  
  unsigned long currentMillis = millis();
  if (sw == 0){
    previousMillis = currentMillis;
    while (digitalRead(BUTTON1)== 0){
      currentMillis = millis();       
      delay(100);
      if (currentMillis - previousMillis >= interval){
        if(Mode == 0){
          Mode = 1;
          SettingMode();
        }else if(Mode == 1){
          Mode = 0;
          TempMode();
        }
        while (digitalRead(BUTTON1)==0){
          delay(10);
        }
     }
   }
 }
}

void TempMode() {
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.println("///Temp///");
  OLED.setCursor(0, 25);
  OLED.setTextSize(1);
  OLED.print("Temp:");
  OLED.print(t);
  OLED.print("(Alert:");
  OLED.print(Count);
  OLED.println(")");
  OLED.print("Humidity:");
  OLED.println(h);
  OLED.display();
  delay(500);
}
void SettingMode() {
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.println("/Setting/");
  OLED.setCursor(0, 25);
  OLED.setTextSize(1);
  OLED.print("Temp:");
  OLED.print(Count);
  OLED.println("(Setting)");
  OLED.print("Humidity:");
  OLED.println(h);
  OLED.display();
  delay(500);
  if(sw2 == 0){
    Count = Count +1;
    delay(100);
  }
  if(Count > 30){
    Count = 25;
  }
}
