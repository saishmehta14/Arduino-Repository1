#include <Servo.h>
#include <LiquidCrystal_I2C.h>
const int trigPin = 12;
const int echoPin = 13;
const int IrSensorPinR = "A2";
const int IrSensorPinL = "A1";
long duration;
int distance;
Servo myServo;

// LiquidCrystal_I2C lcd_1(0x27, 16, 2);

int calculateDistance();

void setup()
{
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pinMode(buzzerPin, OUTPUT);
  // digitalWrite(buzzerPin, LOW);
  // pinMode(5, OUTPUT);
  // pinMode(6, OUTPUT);
  // pinMode(7, OUTPUT);
  Serial.begin(9600);
  myServo.attach(10);
  // lcd_1.init();
  // lcd_1.backlight();
  // lcd_1.print("scanning...");
  myServo.write(180);
}

void loop()
{
  Serial.println("looping.");
  int sensorStateR = digitalRead(A2);
  int sensorStateL = digitalRead(A1);
  
  //  lcd_1.setCursor(0, 1);
  //  lcd_1.print("0");
  delay(10);

  for (int i = 15; i <= 165; i++)
  {
    Serial.println("looping..");

    delay(30);
    myServo.write(i);
    distance = calculateDistance();
    distance = constrain(distance, 5, 100);

    // int targetFrequency = map(distance, 100, 5, 100, 2000);
    if (sensorStateR == LOW)
    {
      Serial.println("object detected by the IR sensor(Right)");
    }
    if (sensorStateL == LOW)
    {
      Serial.println("object detected by the IR sensor(Left)");
    }
    //  lcd_1.clear();

    if ((distance > 5) && (distance < 100))
    {
      Serial.println("looping...");
      // digitalWrite(5, HIGH);
      // digitalWrite(6, LOW);
      // digitalWrite(7, LOW);
      // tone(buzzerPin, targetFrequency);
      //  lcd_1.print("Object Detected!!!");
      // digitalWrite(5, LOW);
      //  lcd_1.print("The distance is: ");
      //  lcd_1.println(distance);
      Serial.println(".");
    }
    else
    {
      Serial.println("looping....");
      //  noTone(buzzerPin);
      // digitalWrite(5,LOW);
      // digitalWrite(6, HIGH);
      // digitalWrite(7, LOW);
      // delay(50);
      // digitalWrite(6,LOW);
    }
  }
  for (int i = 165; i > 15; i--)
  {

    if (sensorStateR == LOW)
    {
      Serial.println("object detected by the IR sensor(Right)");
    }
    if (sensorStateL == LOW)
    {
      Serial.println("object detected by the IR sensor(Left)");
    }

    Serial.println("looping....5");
    delay(30);
    myServo.write(i);
    distance = calculateDistance();
    distance = constrain(distance, 5, 100);

    //int targetFrequency = map(distance, 100, 5, 100, 2000);
    //  lcd_1.clear();
    if ((distance > 5) && (distance < 100))
    {
      Serial.println("looping....6");
      //   digitalWrite(5, HIGH);
      //   digitalWrite(6, LOW);
      //   digitalWrite(7, LOW);
      //   tone(buzzerPin, targetFrequency);
      // //  lcd_1.print("Object Detected!!!");
      //   digitalWrite(5, LOW);
      // //  lcd_1.print("The distance is:");
      // //  lcd_1.println(distance);
      //   Serial.println(".");
    }
    else
    {
      Serial.println("looping....7");
      // noTone(buzzerPin);
      // digitalWrite(5,LOW);
      // digitalWrite(6, HIGH);
      // digitalWrite(7, LOW);
      // delay(50);
      // digitalWrite(6,LOW);
    }
  }
}

int calculateDistance()
{
  Serial.println("looping....8");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);
  return distance;
}
