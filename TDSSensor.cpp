#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Define PWM pins for the Red, Green, and Blue legs
// TDS Sensor Meter V1.0 - Water Quality Monitor

#define TdsSensorPin A1 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1    
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int sensorValue = 0;
float voltage = 0.0;
float tdsValue = 0.0;

void setup() {
  
  pinMode(TdsSensorPin, INPUT);

  Serial.begin(9600);  // Start the serial monitor
  //display.begin(SSD1306_SWITCHCAPVCC,  0x3C );

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(3000);
}

void loop() {
  // Read the analog value from the sensor
  sensorValue = analogRead(TdsSensorPin);
  
  // Convert the analog reading (0-1023) to voltage (assuming 5V reference)
  voltage = sensorValue * 5.0 / 1024.0;
  
  // Convert voltage to TDS value (ppm) using the calibration formula
  tdsValue = abs(133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * 0.5;
  
  // Print numerical results
  Serial.print("~TDS: ");
  Serial.print(tdsValue, 0); // Display as integer
  Serial.println(" ppm | Quality: ");
 
  display.clearDisplay();
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 0);            
  display.print(tdsValue);
  display.println("ppm");
    display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 24); 
  display.setTextSize(1); 
	if (tdsValue < 50) {
		display.println("Excellent");}
	else if (tdsValue >= 50 && tdsValue < 150) {
		display.println("Good");}
	else if (tdsValue >= 150 && tdsValue < 300) {
		display.println("Fair (Harder water)");}
	else if (tdsValue >= 300 && tdsValue <= 500) {
		display.println("Poor");}
	else {
		display.println("Unacceptable (Do not drink!)");
	}
	display.display(); 

  
  delay(2000);  // Wait 2 seconds between readings
}
