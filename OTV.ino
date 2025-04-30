// PIN ASSIGNMENTS

#define IN1 7
#define IN2 6
#define ENA 5

#define IN3 4
#define IN4 3
#define ENB 2

#define TX 10
#define RX 11

// CONSTANTS

#define MARKER_ID 401
#define ROOM_NUMBER 1116

// LIBRARIES

#include "libs/OTV.h"

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Enes100.begin("Oscar", DATA, MARKER_ID, ROOM_NUMBER, TX, RX);
  Enes100.println("Connected");
  Serial.println("Connected");

}

void loop() {
  stage01();
  delay(5000);
}

