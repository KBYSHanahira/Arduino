#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#define echoPin D0
#define trigPin D5

#include <SoftwareSerial.h>
SoftwareSerial Board2(12,13);

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

char Seria[2];
int i = 0;

long duration , cm;
int capacity;


void setup() {
Serial.begin(9600);
Board2.begin(9600);
Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();
delay(2000);

pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);

pinMode(PINSLEDs,OUTPUT);
SLEDs.begin();
SLEDs.show();
}

void loop() {
  while(Board2.available() > 0){
    Seria[i] = Board2.read();
    i++;
    if(i > 2){
      i = 0;
    }
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration*0.034/2;

  char data = Seria[0];
  float DHT22 = Seria[1];
  float DHT22V2 = Seria[2];
  Serial.println(Seria[0]);
  
  
  if(Seria[0] == 'A'){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Temp : ");
    display.println(DHT22);
    display.display();
    Serial.print("Temp : ");
    Serial.println(DHT22);
  }
  //////////////////////////
  if(Seria[0] == 'B'){
    display.clearDisplay();
    display.setCursor(0,25);
    display.println("   Send Ultrasonic");
    display.print("   ");
    display.println(cm);
    display.display();
    Serial.print("Send Ultrasonic  :");
    Serial.println(cm);
  }
  //////////////////////////
  Serial.println(DHT22V2);
  Board2.write(data);
  Board2.write(cm);
  Board2.write(DHT22V2);
  delay(1000);
}
