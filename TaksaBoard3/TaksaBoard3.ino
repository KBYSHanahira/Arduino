#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 14
#define DIO 16

TM1637Display SEG(CLK, DIO);

#include <BH1750.h>
BH1750 lightMeter;

#include <SoftwareSerial.h>
SoftwareSerial Board3(12,13);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

char Seria[2];
int i = 0;
float lux;


void setup() {
Serial.begin(9600);
Board3.begin(9600);
Wire.begin();
lightMeter.begin();

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
  while(Board3.available() > 0){
    Seria[i] = Board3.read();
    i++;
    if(i > 2){
      i = 0;
    }
  }

  float temp = Seria[2];
  lux = lightMeter.readLightLevel();
  char data = Seria[0];
  Serial.println(data);
  float LUX = lux;
  if(Seria[0] == 'D'){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Lux : ");
    display.println(lux);
    display.display();
    Serial.print("Lux  :");
    Serial.println(lux);
  }

  if(Seria[0] == 'C'){
    SEG.setBrightness(0x0f);
    SEG.clear();
    SEG.showNumberDec(temp,true);
  }

  Board3.write(data);
  Board3.write(LUX);
  Board3.write(temp);
  delay(1000);
}
