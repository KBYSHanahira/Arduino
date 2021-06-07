#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 13

#define TEST_DELAY   0

const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
  };

TM1637Display display(CLK, DIO);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

#define echoPin D5
#define trigPin D6

long duration , cm;
int capacity;

void setup() {
Serial.begin(9600);

pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

void loop() {
  display.setBrightness(0x0f);
  display.clear();
  display.showNumberDec(cm, true);
  delay(TEST_DELAY);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(cm);
  
  if(cm > 100){
    SLEDs.setPixelColor(0,SLEDs.Color(0,255,0));
    SLEDs.setPixelColor(1,SLEDs.Color(0,255,0));
    delay(2000);
    tone(D8,2000,100);
  }
  if(cm < 100){
    SLEDs.setPixelColor(0,SLEDs.Color(255,128,0));
    SLEDs.setPixelColor(1,SLEDs.Color(255,128,0));
    delay(150);
    tone(D8,2000,100);
  }
  if(cm < 50){
    SLEDs.setPixelColor(0,SLEDs.Color(255,0,0));
    SLEDs.setPixelColor(1,SLEDs.Color(255,0,0));
    tone(D8,2000);
    }
  SLEDs.show();
  delay(250);
}
