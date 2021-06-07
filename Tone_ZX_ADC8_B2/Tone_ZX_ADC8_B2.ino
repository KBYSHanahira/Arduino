#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10

Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);


SoftwareSerial Board2 (12,14);
char loli[2];
int i=0;
int volume2;
////////////////////////////////////////////////////////////////
void setup(){
Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
Serial.begin(9600);
Board2.begin(9600);

display.display();
delay(2000);
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

/////////////////////////////////////
void loop(){
  while (Board2.available() > 0) {
    loli[i] = Board2.read();
    i++;
    if(i > 1){
      i = 0;
    }
  }
int lolix = loli[1];
///////////////////////////
volume2 = analogRead(A0);

int Reback = map(loli[2],0,255,0,1024);

if(loli[0] == '2'){
  tone(D8,2000,1000);
  loli[0] = 0;
}
if(loli[0] == 'B'){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("ZX-POTV2 :");
  display.println(volume2);
  display.display();
  delay(100);
}
if(loli[0] == 'C'){
  display.clearDisplay();
  display.display();
  delay(100);
  Board2.write(volume2);
}
if(loli[0] == 'D'){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("ZX-POTV1 :");
  display.println(lolix);
  display.display();
  delay(100);
}

if(loli[0] == 'F'){
  SLEDs.setPixelColor(1, SLEDs.Color(255,255,255));
  SLEDs.show();
}else{
  SLEDs.setPixelColor(0, SLEDs.Color(0,0,0));
  SLEDs.show();
}
}
