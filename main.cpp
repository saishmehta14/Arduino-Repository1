#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <thingProperties.h>

#define TdsSensorPin A1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensorValue = 0;
float voltage = 0.0;
float tdsValue = 0.0;
unsigned long lastReadMs = 0;
const unsigned long READ_INTERVAL_MS = 2000;

String getWaterQuality();
void readSensorAndDisplay();

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(TdsSensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Arduino Cloud's connection handler owns the WiFi connection.
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  // Must run frequently: keeps the cloud connection alive and publishes PPM when it changes.
  ArduinoCloud.update();

  if (millis() - lastReadMs >= READ_INTERVAL_MS) {
    lastReadMs = millis();
    readSensorAndDisplay();
  }
}

void readSensorAndDisplay() {
  sensorValue = analogRead(TdsSensorPin);
  voltage = sensorValue * 5.0 / 1024.0;
  tdsValue = abs(133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * 0.5;
  PPM = tdsValue;

  Serial.print("~TDS: ");
  Serial.print(tdsValue, 0);
  Serial.println(" ppm");

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(tdsValue);
  display.println("ppm");
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.println(getWaterQuality());
  display.display();
}

String getWaterQuality() {
  if (tdsValue < 50)        return "Excellent";
  else if (tdsValue < 150)  return "Good";
  else if (tdsValue < 300)  return "Fair (Harder water)";
  else if (tdsValue <= 500) return "Poor";
  else                      return "Unacceptable (Do not drink!)";
}

/*
  Since Ppm is READ_WRITE variable, onPpmChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPpmChange()  {
  // The TDS sensor is the source of truth: discard values written from the
  // dashboard and re-publish the latest measured reading.
  Serial.print("Cloud wrote PPM = ");
  Serial.print(PPM, 0);
  Serial.print(", restoring sensor value ");
  Serial.println(tdsValue, 0);
  PPM = tdsValue;
}
