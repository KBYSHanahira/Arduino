#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10

Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);


SoftwareSerial Board2 (2,14);

int loli[2];

float volume1;
float volume2;

void setup(){
Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

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
 int i=0;
void loop(){
/////////////////////////////////////////////////////////////////
while (Board2.available() > 0) {
    loli[i] = Board2.read();
    i++;
    if(i > 2){
      i = 0;
    }
  }
volume1 = map (loli[0],0,255,0,4095);
volume2 = map (loli[1],0,255,0,4095);
display.clearDisplay();
display.setCursor(0, 0);
display.print("VR1 :");
display.println(volume1);
display.print("VR2 :");
display.println(volume2);
display.display();
delay(100);

if(loli[2] == 'R'){
    SLEDs.setPixelColor(0, SLEDs.Color(255,0,0));
    SLEDs.setPixelColor(1, SLEDs.Color(255,0,0));
    SLEDs.show();
  }else if(loli[2] == 'G'){
    SLEDs.setPixelColor(0, SLEDs.Color(0,255,0));
    SLEDs.setPixelColor(1, SLEDs.Color(0,255,0));
    SLEDs.show();
  }else if(loli[2] == 'B'){
    SLEDs.setPixelColor(0, SLEDs.Color(0,0,255));
    SLEDs.setPixelColor(1, SLEDs.Color(0,0,255));
    SLEDs.show();
  }
  
}
