#include <LEDMatrixDriver.hpp>
#include <ESP8266WiFi.h>
#include <time.h>

// WiFi Config
#define WIFI_SSID     "@IOT323"
#define WIFI_PASSWORD "IOT11223344"

// NTP Config
int timezone = 7 * 3600;
int dst = 0;

// Dot Matrix
const uint8_t LEDMATRIX_CS_PIN = D8;
const int LEDMATRIX_WIDTH = 31;
const int LEDMATRIX_HEIGHT = 7;
const int LEDMATRIX_SEGMENTS = 4;

LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

extern void drawTime(String strTime, int offset = 0) ;

String lastTimeStr;
unsigned long lastShowColon = 0;
bool showColon = false;

void setup() {
  Serial.begin(115200);

  lmd.setEnabled(true);
  lmd.setIntensity(2);

  // Connect WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" Connected");

  // Get time from NTP server
  configTime(timezone, dst, "ntp.ku.ac.th", "fw.eng.ku.ac.th", "ilm.live.rmutt.ac.th");
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" OK");
}

void loop()  {
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);

  if ((millis() - lastShowColon) >= 500) {
    lastShowColon = millis();
    
    showColon = !showColon;
  }
  
  String timeStr = "";
  timeStr += p_tm->tm_hour < 10 ? "0" : "";
  timeStr += p_tm->tm_hour;
  
  timeStr += showColon ? ":" : " ";
  timeStr += p_tm->tm_min < 10 ? "0" : "";
  timeStr += p_tm->tm_min;

  if (timeStr != lastTimeStr) {
    drawTime(timeStr, 2);
    lastTimeStr = timeStr;
  }
  
  delay(10);
}
