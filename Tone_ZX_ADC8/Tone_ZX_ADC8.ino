#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <SoftwareSerial.h>

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10

Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

SoftwareSerial Board1 (12,14);

char Moe;
char Koi;
int volume1;
/////////////////////////////////////////////////////
void setup(){
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
///////////////////////////////////////////////////
void loop(){
  while (Serial.available() > 0) {
    Moe = Serial.read();
    Board1.write(Moe);
  }
  while (Board1.available() > 0){
    Koi = Board1.read();
  }

/////////////////////////////////////////////////////
volume1 = analogRead(A0);

int Recive = map(Koi,0,255,0,1024);

if(Moe == '1'){
  tone (D8,2000,1000);
  Moe = 0;
}

if(Moe == '2'){
  Moe = 0;
}

if(Moe == 'A'){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("ZX-POTV1 :");
  display.println(volume1);
  display.display();
  delay(100);
}
if(Moe == 'B'){
  display.clearDisplay();
  display.display();
}
if(Moe == 'C'){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("ZX-POTV2 :");
  display.println(Recive);
  display.display();
  delay(100);
}
if(Moe == 'D'){
  Board1.write(volume1);
  display.clearDisplay();
  display.display();
  delay(100);
}
if(Moe == 'E'){
  SLEDs.setPixelColor(1, SLEDs.Color(255,255,255));
  SLEDs.show();
}else{
  SLEDs.setPixelColor(0, SLEDs.Color(0,0,0));
  SLEDs.show();
}
delay(500);
}
