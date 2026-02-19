#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include "time.h"

#define PIN 17

// Matrix Setup: 32 wide, 8 high
// NEO_MATRIX_TOP + NEO_MATRIX_LEFT: First pixel is top left
// NEO_MATRIX_COLUMNS: Pixels are arranged in columns
// NEO_MATRIX_ZIGZAG: The wiring bounces back and forth
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* ntpServer = "pool.ntp.org";

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(64);
  matrix.setTextColor(matrix.Color(0xE0, 0x10, 0xFF)); // Purple

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  configTime(28800, 0, ntpServer); // 时区，夏令时，时间服务器
  // 28800 = 8小时 = 东8区
}

char previousTimeString[6] = { 0 };
void loop() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }

  char timeString[6];
  sprintf(timeString, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);

  matrix.fillScreen(0);    // 清屏
  matrix.setCursor(1, 1);
  
  if (previousTimeString != timeString) { // 减少不必要的刷新
    matrix.print(timeString);
    matrix.show();
    for (int i = 0; i < 6; i++) {
      previousTimeString[i] = timeString[i];
    }
  }

  delay(1000); 
}