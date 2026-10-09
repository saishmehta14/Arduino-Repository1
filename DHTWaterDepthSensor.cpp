#include <DHT.h>
#include <LiquidCrystal_I2C.h>
// Define DHT Sensor Pins and Type
#define DHTPIN 8     // Signal pin connected to Digital Pin 2
#define DHTTYPE DHT11
int waterSensorPin = A0;
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
void setColor(int redValue, int greenValue, int blueValue);
LiquidCrystal_I2C lcd_1(0x27, 16, 2);
// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600);


  // Set all three color pins as outputs
  pinMode(DHTPIN, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(waterSensorPin, INPUT);
  lcd_1.init();
  lcd_1.backlight();
  lcd_1.print("DHT scanning...");
  dht.begin();
}

void loop() {
  // Show Red
  // Read temperature as Celsius (default)

  delay(2000);
  lcd_1.clear();
  float tempF = dht.readTemperature(true);
  float humidity = dht.readHumidity();
  Serial.println(tempF);
  if (isnan(tempF)) 
  {
    Serial.println("Failed to read from DHT11 sensor!");
    // Blink Blue to indicate a sensor error
    setColor(255, 0, 255); 
    delay(200);
    setColor(255, 0, 255);
    return;
  }
  int sensorValue = analogRead(waterSensorPin);

  //Print out the value you read
  Serial.print("Water Level: ");
  Serial.println(sensorValue);

  if (tempF > 85)
  {  
    // Show Red
    setColor(255, 0, 0);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Temp is: ");
    lcd_1.print(tempF);
    lcd_1.print((char)223); // Degree symbol character
    lcd_1.println("F");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Humidity: ");
    lcd_1.print(humidity);  
    lcd_1.println("%");

    
    delay(10000);
  }
  else if (tempF > 68)
  {
    // Show Green
    setColor(0, 255, 0);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Temp is: ");
    lcd_1.print(tempF);
    lcd_1.print((char)223); // Degree symbol character
    lcd_1.println("F");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Humidity: ");
    lcd_1.print(humidity);  
    lcd_1.println("%");    
    delay(10000);
  }
  else
  {
    // Show Blue
    setColor(0, 0, 255);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Temp is: ");
    lcd_1.print(tempF);
    lcd_1.print((char)223); // Degree symbol character
    lcd_1.println("F");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Humidity: ");
    lcd_1.print(humidity);  
    lcd_1.println("%");   
    delay(10000);
  }
  // Show Purple (Mix Red and Blue)
  setColor(0, 0, 0);
}

// Easy function to mix colors (Red, Green, Blue) values from 0 to 255
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
