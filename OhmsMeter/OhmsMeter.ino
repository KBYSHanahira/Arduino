#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);


#include <Adafruit_NeoPixel.h>
#define NUMSLEDs 2
#define PINSLEDs 10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

float R = 1000;
float Vcc = 3.3;
float Vx;
float Rx;
int loli = 1;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  delay(5000);

  pinMode(PINSLEDs,OUTPUT);
  SLEDs.begin();
  SLEDs.show();
}


void loop() {

  if (digitalRead(D7) == 0) {
    tone(D8, 1000, 500);
    loli = loli + 1;
    while (digitalRead(D7) == 0) {
      if (loli > 3) {
        loli = 1;
      }
      delay(100);
    }
  }
  if (loli == 1) {
    int Val = analogRead(A0);
    Vx = (Val * Vcc) / 1024;
    Serial.println(Val);
    Rx = (Vx * R) / (Vcc - Vx);
    Serial.print(Rx);
    Serial.println("  Ohms");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Use Range x1 Ohms:");
    display.setCursor(0, 25);
    display.print("Value : ");
    display.print(Rx);
    display.print(" Ohms");
    display.display();
    delay(500);
  }

  if (loli == 2) {
    int Val = analogRead(A0);
    Vx = (Val * Vcc) / 1024;
    Rx = ((Vx * R ) / (Vcc - Vx) / 1000);
    Serial.print(Rx);
    Serial.println("  K Ohms");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Use Range 1 K Ohms:");
    display.setCursor(0, 25);
    display.print("Value : ");
    display.print(Rx);
    display.println(" K Ohms");
    display.display();
    delay(500);
  }

  if (loli == 3) {
    int Val = analogRead(A0);
    Vx = (Val * Vcc) / 1024;
    Rx = ((Vx * R ) / (Vcc - Vx) / 10000);
    Serial.print(Rx);
    Serial.println("  K Ohms");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Use Range 10 K Ohms:");
    display.setCursor(0, 25);
    display.print("Value : ");
    display.print(Rx);
    display.print(" K Ohms");
    display.display();
    delay(500);
  }
}
