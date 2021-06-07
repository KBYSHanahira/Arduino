#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

int ZX_POTV;
int volume;
int Freq;

bool PUSH;
bool PUSHA;
bool PUSHB;
bool PUSHC;


int Mode;
void setup() {
Serial.begin(9600);

Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

void loop() {
  ZX_POTV = analogRead(A0);
  volume = map(ZX_POTV,0,1024,1,3);
  Serial.println(volume);
  PUSH = digitalRead(D7);
  
  if(volume == 1){
    First1();
  }else if(volume == 2){
    First2();
  }else if(volume == 3){
    First3();
  }
  
  while(Mode == 1){
   Second(); 
  }
  while(Mode == 2){
   Third(); 
  }
  while(Mode == 3){
   Force(); 
  }
}

void First1(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("-->");
  display.print(" SLED1");
  display.setCursor(0,25);
  display.print("   ");
  display.print(" SLED2");
  display.setCursor(0,50);
  display.print("   ");
  display.print(" SPK");
  display.display();
  delay(200);
 if(digitalRead(13) == 0){
  while(digitalRead(13) == 0){
      delay(1);
    }
    Mode = 1;
  }
}

void First2(){
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0, 0);
display.print("   ");
display.print(" SLED1");
display.setCursor(0,25);
display.print("-->");
display.print(" SLED2");
display.setCursor(0,50);
display.print("   ");
display.print(" SPK");
display.display();
delay(200);
if(digitalRead(13) == 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    Mode = 2;
}
}

void First3(){
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0, 0);
display.print("   ");
display.print(" SLED1");
display.setCursor(0,25);
display.print("   ");
display.print(" SLED2");
display.setCursor(0,50);
display.print("-->");
display.print(" SPK");
display.display();
delay(200);
if(digitalRead(13) == 0){
    while(digitalRead(13) == 0){
      delay(1);
    }
    Mode = 3;
  }
}
