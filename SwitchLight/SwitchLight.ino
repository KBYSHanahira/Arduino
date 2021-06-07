#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <BH1750.h>
BH1750 lightMeter;

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

int Mode = 0;

unsigned long previousMillis = 0;

float lux;

void setup() {
Serial.begin(9600);
Wire.begin();

lightMeter.begin();

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.display();
delay(2000);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

void loop() {
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.println(lux);
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("   LUX");
  display.print("> ");
  display.println(lux);
  display.println("   Mode");
  display.print("> ");
  display.println(Mode);
  display.display();
  delay(250);
  
  unsigned long currentMillis = millis();
  
  if (lux < 100){
    previousMillis = currentMillis;
    while (lux < 100){
      currentMillis = millis();    
      delay(100);
      if(currentMillis - previousMillis >= 3000){
        Mode++;
        while (lux < 100){
          delay(10);
          lux = 120;
        }
          if(Mode == 1){
            SLEDs.setPixelColor(0,SLEDs.Color(255,0,0));
            SLEDs.setPixelColor(1,SLEDs.Color(255,0,0));
            SLEDs.show();
            tone(D8,1000,1000);
          }
 
          if(Mode == 2){
            SLEDs.setPixelColor(0,SLEDs.Color(0,255,0));
            SLEDs.setPixelColor(1,SLEDs.Color(0,255,0));
            SLEDs.show();
            tone(D8,2000,1000);
          }

          if(Mode == 3){
            SLEDs.setPixelColor(0,SLEDs.Color(0,0,255));
            SLEDs.setPixelColor(1,SLEDs.Color(0,0,255));
            SLEDs.show();
            tone(D8,3000,1000);
          }

          if(Mode == 4){
            SLEDs.setPixelColor(0,SLEDs.Color(255,128,0));
            SLEDs.setPixelColor(1,SLEDs.Color(255,128,0));
            SLEDs.show();
            tone(D8,4000,1000);
          }

          if(Mode == 5){
            SLEDs.setPixelColor(0,SLEDs.Color(128,0,255));
            SLEDs.setPixelColor(1,SLEDs.Color(128,0,255));
            SLEDs.show();
            tone(D8,5000,1000);
          }
          if(Mode > 5){
            Mode = 0;
          }
     }
   }
 }else{
  delay(10);
 }
 if(Mode == 0){
    SLEDs.setPixelColor(0,SLEDs.Color(0,0,0));
    SLEDs.setPixelColor(1,SLEDs.Color(0,0,0));
    SLEDs.show();
 }
}
