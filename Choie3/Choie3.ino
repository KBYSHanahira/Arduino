#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial

#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);
char auth[] = "aaecc87193e84b8f8142b2a84c96a096";
char ssid[] = "NoGameNoLife";
char pass[] = "NGNLZERO";

int Mode = 0;
int VR1;
int VR2;
int VR3;


void setup() {
Serial.begin(9600);
Wire.begin();
Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);
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
  int ch0 = 0; 
  int mode = 1;
  int ADC8Ch0 = readADS7828(B10010001,ch0, mode);
  int ch1 = 1; 
  int ADC8Ch1 = readADS7828(B10010001, ch1, mode);

  int volume = analogRead(A0);
  
  int VR1 = map(volume,0,1024,0,100);
  int VR2 = map(ADC8Ch0,0,4095,0,14);
  int VR3 = map(ADC8Ch1,0,4095,0,1001);
  Serial.println(VR1);
  
  display.clearDisplay();
  display.setCursor(30,10);
  display.print("Hud=");   
  display.print(VR1);
  display.println("%");
  display.setCursor(30,30);
  display.print("Ph=");   
  display.println(VR2);
  display.setCursor(30,50);
  display.print("Light=");   
  display.println(VR3);
  display.display();
  delay(100);

  Blynk.run();
  Blynk.virtualWrite(V1,VR1);
  Blynk.virtualWrite(V2,VR2);
  Blynk.virtualWrite(V3,VR3);
}

BLYNK_WRITE(V4){
  int ch0 = 0; 
  int mode = 1;
  int ADC8Ch0 = readADS7828(B10010001,ch0, mode);
  int ch1 = 1; 
  int ADC8Ch1 = readADS7828(B10010001, ch1, mode);
  
  int volume = analogRead(A0);
  
  int VR1 = map(volume,0,1024,0,100);
  int VR2 = map(ADC8Ch0,0,4095,0,14);
  int VR3 = map(ADC8Ch1,0,4095,0,1001);
  
    if(VR1 < 20){
      digitalWrite(D6,HIGH);
    }
    if(VR1 > 50){
      digitalWrite(D6,LOW);
    }
    if(VR3 < 100){
      digitalWrite(D7,HIGH);
    }
    if(VR3 > 300){
        digitalWrite(D7,LOW);
    }
}

unsigned int readADS7828(unsigned char ads_address, unsigned char channel, bool mode)
{
  ads_address = ads_address >> 1 ; //
  // command address for the channels, allows 0-7 channel mapping in the correct order
  unsigned char channels[8] = {0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70};
  unsigned char command = 0;    // Initialize command variable
  unsigned int reading = 0;     // Initialize reading variable

  command = channels[channel];    // put required channel address in command variable

  if (mode) {                     // mode = 1 Single-ended input, mode = 0 Differential input
    command = command ^ 0x80;     // Enable Single-ended mode (toggle MSB, SD bit in datasheet)
  }

  Wire.beginTransmission(ads_address);  // Send a start or repeated start command with a slave address and the R/W bit set to '0' for writing.
  Wire.write(command);            // Then send a command byte for the register to be read.
  Wire.endTransmission();       // Send stop command
  delay(10);
  Wire.requestFrom(ads_address, 2);   // Request 2 bytes from the ADC
  if (2 <= Wire.available())      // if two bytes were received
  {
    reading = Wire.read();        // receive high byte
    reading = reading << 8;       // shift high byte to be high 8 bits
    reading |= Wire.read();       // receive low byte into lower 8 bits
  }
  return reading;         // return the full 12 bits reading from the ADC channel
}
