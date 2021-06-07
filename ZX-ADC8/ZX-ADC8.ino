#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "42c7692004b5408bb865b34a0e98ee93";
char ssid[] = "microlab";
char pass[] = "20182019";

Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);


SoftwareSerial Board1 (2,14);

float volume1;
float volume2;

int vo1;
int vo2;
char bink;

void setup(){
Serial.begin(9600);
Board1.begin(9600);
Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);

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

void loop(){
display.clearDisplay();
display.setCursor(0, 0);

/////////////////////////////////////////////////////////////////
int ch0 = 0;
int mode = 1; // mode = 1 Single-ended, mode = 0 Differential
int ADC8Ch0 = readADS7828(B10010001,ch0, mode);// Read analog CH0
display.print("Volume" + String(ch0) + " = ");
display.println(String(ADC8Ch0) + " "); // Display analog CH0
/////////////////////////////////////////////////////////////////
int ch1 = 1;
int ADC8Ch1 = readADS7828(B10010001, ch1, mode);// Read analog CH1
display.print("Volume" + String(ch1) + " = ");
display.println(String(ADC8Ch1) + " "); // Display analog CH1
display.display();
delay(100);

vo1 = ADC8Ch0;
vo2 = ADC8Ch1;

volume1 = map(ADC8Ch0,0,4095,0,255);
volume2 = map(ADC8Ch1,0,4095,0,255);

Serial.println(volume1);
Serial.println(volume2);
/////////////////////////////////////////////////////////////////
Board1.write(ADC8Ch0);
Board1.write(ADC8Ch1);
Board1.write(bink);
Board1.flush();
Blynk.run();
}

BLYNK_READ(V1){
  Blynk.virtualWrite(V1,vo1);
}
BLYNK_READ(V2){
  Blynk.virtualWrite(V2,vo2);
}

BLYNK_WRITE(V3){
  bink = 'R';
}

BLYNK_WRITE(V4){
  bink = 'G';
}

BLYNK_WRITE(V5){
  bink = 'B';
}



unsigned int readADS7828(unsigned char ads_address, unsigned char channel, bool mode){
ads_address = ads_address >> 1 ;
unsigned char channels[8] = {0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70};
unsigned char command = 0;
unsigned int reading = 0;
command = channels[channel];

if (mode){
command = command ^ 0x80;
}
Wire.beginTransmission(ads_address);
Wire.write(command);
Wire.endTransmission();
delay(10);
Wire.requestFrom(ads_address, 2);
if (2 <= Wire.available()){
reading = Wire.read();
reading = reading << 8;
reading |= Wire.read();
}
return reading;
}
