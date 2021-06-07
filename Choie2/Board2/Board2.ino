#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <SoftwareSerial.h>
SoftwareSerial Board2(D7,D6);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_GRB + NEO_KHZ800);

int Mode = 0;

void setup() {
Serial.begin(9600);
Board2.begin(9600);
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
  while (Board2.available() > 0) {
    Serial.write(Board2.read());
  }
  while (Serial.available() > 0) {
    Board2.write(Serial.read());
  }
}
