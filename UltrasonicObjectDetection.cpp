#include <Arduino.h>
#include <Servo.h>

Servo myServo;

const int trigPin = 5;

const int echoPin = 6;

int i = 0;

long duration;

float distance;

#include <MD_MAX72xx.h>
#include <SPI.h>

int rowsON = 0;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define MAX_DEVICES 1

#define CS_PIN 10

MD_MAX72XX matrix = MD_MAX72XX(

    HARDWARE_TYPE, CS_PIN, MAX_DEVICES

);

void func();

void setup()

{
  Serial.begin(9600);

  matrix.begin();

  matrix.control(MD_MAX72XX::INTENSITY, 5);

  matrix.clear();

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  pinMode(8, OUTPUT);

  pinMode(3, OUTPUT);

  myServo.attach(3);
}

void loop()

{
  // myServo.write(0);

  delay(200);

  for (i = 1; i <= 165; i++) {
    {
      myServo.write(i);

      func();
    }
  }

  for (i = 165; i >= 0; i--) {
    {
      myServo.write(i);

      func();
    }
  }
}

void func() {
  int constrainedDistance = constrain(distance, 0, 60);

  // Send ultrasonic pulse

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Measure returning pulse

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    Serial.println("Out of range");

  } else {
    // Calculate distance in centimeters

    distance = duration * 0.0343 / 2;

    Serial.print("Distance: ");

    Serial.print(distance);

    Serial.print(" cm");
  }

  int freq = map(constrainedDistance, 0, 60, 2000, 100);

  // map distance (2, 60, 2000, 100)

  if (distance <= 10) {
    rowsON = 8;

    tone(8, freq);

  }

  else if (distance <= 20) {
    rowsON = 6;

    tone(8, freq);

  }

  else if (distance <= 30) {
    rowsON = 4;

    tone(8, freq);

  }

  else if (distance <= 40) {
    rowsON = 2;

    tone(8, freq);

  }

  else if ((distance > 40) && (distance <= 60)) {
    rowsON = 1;

    noTone(8);
  }

  matrix.clear();

  Serial.print(" Frequency = ");

  Serial.print(freq);

  Serial.println(" Hz");

  for (int row = 0; row < rowsON; row++) {
    matrix.setRow(0, 7 - row, 0xFF);

    // delay(100);
  }
}
