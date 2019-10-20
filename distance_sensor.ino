// This uses Serial Monitor to display Range Finder distance readings

#include "NewPing.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define TRIGGER_PIN  10
#define ECHO_PIN     13
#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float duration, distance;

int iterations = 5;

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() {
  Serial.begin (9600);
  matrix.begin(0x70);
}

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };

void loop() {
   
  duration = sonar.ping_median(iterations);
  distance = (duration / 2) * 0.0343;
  matrix.clear();
  
  if (distance < 20 && distance >= 2) {
    Serial.println("Perfect range!");
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
  }
  else if (distance < 50 && distance > 20) {
    matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    Serial.println("Getting too far.");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  else {
    matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
    Serial.print("Out of range!!!");
    Serial.println(" cm");
    delay(500);
  }
  delay(500);
}
