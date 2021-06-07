#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_GRB + NEO_KHZ800);


void setup() {
Serial.begin(9600);
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
  int VR = analogRead(A0);
  VR = map(VR,0,1024,1,6);
  if(VR == 1){
    display.clearDisplay();
    display.setCursor(5,15);
    display.setTextSize(1);
    display.print("Color");
    display.setCursor(5,25);
    display.setTextSize(2);
    display.println("RED");
    display.display();
    if(digitalRead(D5)==0){
      SLEDs.setPixelColor(0, SLEDs.Color(255,0,0));
      SLEDs.show();
    }
    if(digitalRead(D6)==0){
      SLEDs.setPixelColor(1, SLEDs.Color(255,0,0));
      SLEDs.show();
    }
  }
  if(VR == 2){
    display.clearDisplay();
    display.setCursor(5,15);
    display.setTextSize(1);
    display.print("Color");
    display.setCursor(5,25);
    display.setTextSize(2);
    display.println("GREEN");
    display.display();
    if(digitalRead(D5)==0){
      SLEDs.setPixelColor(0, SLEDs.Color(0,255,0));
      SLEDs.show();
    }
    if(digitalRead(D6)==0){
      SLEDs.setPixelColor(1, SLEDs.Color(0,255,0));
      SLEDs.show();
    }
  }
  if(VR == 3){
    display.clearDisplay();
    display.setCursor(5,15);
    display.setTextSize(1);
    display.print("Color");
    display.setCursor(5,25);
    display.setTextSize(2);
    display.println("BLUE");
    display.display();
    if(digitalRead(D5)==0){
      SLEDs.setPixelColor(0, SLEDs.Color(0,0,255));
      SLEDs.show();
    }
    if(digitalRead(D6)==0){
      SLEDs.setPixelColor(1, SLEDs.Color(0,0,255));
      SLEDs.show();
    }
  }
  if(VR == 4){
    display.clearDisplay();
    display.setCursor(5,15);
    display.setTextSize(1);
    display.print("Color");
    display.setCursor(5,25);
    display.setTextSize(2);
    display.println("YELLOW");
    display.display();
    if(digitalRead(D5)==0){
      SLEDs.setPixelColor(0, SLEDs.Color(255,255,0));
      SLEDs.show();
    }
    if(digitalRead(D6)==0){
      SLEDs.setPixelColor(1, SLEDs.Color(255,255,0));
      SLEDs.show();
    }
  }
  if(VR == 5){
    display.clearDisplay();
    display.setCursor(5,15);
    display.setTextSize(1);
    display.print("Color");
    display.setCursor(5,25);
    display.setTextSize(2);
    display.println("WHITE");
    display.display();
    if(digitalRead(D5)==0){
      SLEDs.setPixelColor(0, SLEDs.Color(255,255,255));
      SLEDs.show();
    }
    if(digitalRead(D6)==0){
      SLEDs.setPixelColor(1, SLEDs.Color(255,255,255));
      SLEDs.show();
    }
  }
  if(VR == 6){
    display.clearDisplay();
    display.setCursor(5,15);
    display.setTextSize(1);
    display.print("Color");
    display.setCursor(5,25);
    display.setTextSize(2);
    display.println("OFF");
    display.display();
    if(digitalRead(D5)==0){
      SLEDs.setPixelColor(0, SLEDs.Color(0,0,0));
      SLEDs.show();
    }
    if(digitalRead(D6)==0){
      SLEDs.setPixelColor(1, SLEDs.Color(0,0,0));
      SLEDs.show();
    }
  }
}
