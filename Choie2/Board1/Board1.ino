#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <SoftwareSerial.h>
SoftwareSerial Board1(D4,D5);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_GRB + NEO_KHZ800);

String Code;

void setup() {
Serial.begin(9600);
Board1.begin(9600);
Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();
delay(2000);

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

void loop() {
  while (Serial.available() > 0) {
    Code = Serial.read();
  }
if(Code == "AP"){
  tone(D8,1000,1000);
}
}
