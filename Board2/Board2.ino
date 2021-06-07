#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1);

#define Switch 13

String loli;
int count = 1;

SoftwareSerial Board2 (14, 12, false, 256);

void setup() {
  Serial.begin(9600);
  Board2.begin(9600);
  pinMode(Switch,INPUT);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  while (Board2.available() > 0) {
    loli = Board2.read();
  }
  int sw = digitalRead(Switch);
  if(sw == 0){
    count = count + 1;
  }
  Serial.println(count);
  if(count == 1){
    Board2.write(count);
  }

  if(count == 2){
    Board2.write(count);
  }

  if(count == 3){
    Board2.write(count);
  }

  if(count == 4){
    Board2.write(count);
  }

  if(count > 4){
    count = 1;
  }
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.print("Temp :");
  OLED.println(loli);
  OLED.setCursor(0, 25);
  OLED.display();
  delay(200);
}
