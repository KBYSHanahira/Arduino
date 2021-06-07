#include <Adafruit_NeoPixel.h>
#define PIN            10
#define NUMPIXELS      2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1);

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <AuthClient.h>
#include <MicroGear.h>
#include <MQTTClient.h>
#include <SHA1.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
const char* ssid = "NoGameNoLife";
const char* password = "NGNLZERO";
#define APPID "ControlRGB"
#define APPKEY "yodbmOWHy3tGK0Z"
#define APPSECRET "CUx10L3CPnk3FfxMcO2Q7N376"
#define ALIAS "SmartRGB"
int timer = 0;
int LEDPin = 10;
int st;
float t;
float h;
WiFiClient client;
AuthClient *authclient;
MicroGear microgear(client);
unsigned long previousMillis = 0;
const long interval = 1000;
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen){
  Serial.print("Incoming message —> ");
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
  for (int i = 0; i < msglen; i++)
  {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
  Serial.println();
  String Topic = topic;
  String stateStr = String(strState).substring(0, msglen);
  if (Topic.equals("/ControlRGB/Send_RGB")){
    st = stateStr.toInt();
    Serial.println(st);
    digitalWrite(LEDPin, st);
    if (st == 1){
      microgear.publish("/Feedback_RGB/Status", "RED", 1);
    }else if (st == 2){
      microgear.publish("/Feedback_RGB/Status", "GREEN", 1);
    }else if (st == 3){
      microgear.publish("/Feedback_RGB/Status", "BLUE", 1);
    }else if (st == 0){
      microgear.publish("/Feedback_RGB/Status", "OFF", 1);
    }
  }
}
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen){
  Serial.println("Connected to NETPIE....Now..");
  microgear.subscribe("/Send_RGB");
  microgear.publish("/TempStatus/",t);
  microgear.publish("/Humidity/",h);
}
void setup(){
  pixels.begin();
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(115200);
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);
  Serial.println("Starting...");
  pinMode(LEDPin, OUTPUT);
  if (WiFi.begin(ssid, password)){
    OLED.clearDisplay();
    while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
      OLED.setTextColor(WHITE);
      OLED.setCursor(0, 0);
      OLED.setTextSize(2);
      OLED.println("Connecting.....");
      OLED.display();
    }
    }
    Serial.println("WiFi connected" + WiFi.SSID());
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    OLED.clearDisplay();
    OLED.setTextColor(WHITE);
    OLED.setCursor(0, 0);
    OLED.setTextSize(1);
    OLED.println("WiFi :" + WiFi.SSID());
    OLED.println("IP :");
    OLED.print(WiFi.localIP());
    OLED.display();
    delay(5000);
    OLED.clearDisplay();
    OLED.display();
    //uncomment the line below if you want to reset token —>
    //microgear.resetToken();
    microgear.init(APPKEY, APPSECRET, ALIAS);
    microgear.connect(APPID);
  }
void loop(){
  t = dht.readTemperature();
  h = dht.readHumidity();
  
  if (microgear.connected()){
    microgear.loop();
  }else{
    Serial.println("connection lost, reconnect...");
    OLED.clearDisplay();
    OLED.setTextColor(WHITE);
    OLED.setCursor(0, 0);
    OLED.setTextSize(1);
    OLED.println("Cennect Lost, Reconnect...");
    OLED.display();
    microgear.connect(APPID);
    delay(timer);
    timer += 100;
  }
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(1);
  OLED.println("Incoming message : ");
  OLED.setTextSize(3);
  if (st == 1){
    pixels.setPixelColor(1, pixels.Color(150,0,0));
    pixels.setPixelColor(0, pixels.Color(150,0,0));
    OLED.println("RED");
    
  } else if(st == 2){
    pixels.setPixelColor(1, pixels.Color(0,150,0));
    pixels.setPixelColor(0, pixels.Color(0,150,0));
    OLED.println("GREEN");
  }else if(st == 3){
    pixels.setPixelColor(1, pixels.Color(0,0,150));
    pixels.setPixelColor(0, pixels.Color(0,0,150));
    OLED.println("BLUE");
  }else if(st == 0){
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    OLED.println("OFF");
  }
  OLED.display();
  pixels.show();
}
