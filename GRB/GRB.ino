#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
#include <DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT11
#define PIN 10
#define NUMPIXELS 2
#define BLYNK_PRINT Serial
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
char auth[] = "5d0ddb7df106488d81cdb6b1e74f3fde";
char ssid[] = "NoGameNoLifeZero";
char pass[] = "NGNLZERO";

void setup()
{
  // Debug console
  Serial.begin(9600);

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(1000L, sendSensor);
  pixels.begin();
  dht.begin();
}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1)
{

int R = param[0].asInt();
int G = param[1].asInt();
int B = param[2].asInt();
for(int i=0;i<NUMPIXELS;i++){

pixels.setPixelColor(i, pixels.Color(R,G,B));

pixels.show();
}
Serial.println("----------------------");
Serial.println("RED :");
Serial.println(R);
Serial.println("GREEN :");
Serial.println(G);
Serial.println("BLUE :");
Serial.println(B);
Serial.println("----------------------");
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, t);
  Serial.println(t);
  Serial.println("----------------------");
}
