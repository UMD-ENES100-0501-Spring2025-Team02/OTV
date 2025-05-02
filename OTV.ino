// PIN ASSIGNMENTS

#define IN1 7
#define IN2 6
#define ENA 5

#define IN3 4
#define IN4 3
#define ENB 2

#define TX 10
#define RX 11

#define REED1 A0
#define REED2 A1
#define REED3 A2

#define LEFT_LIMIT A3
#define RIGHT_LIMIT A4

#define DUTY_PIN 8

#define CLAW_SERVO_PIN 12
#define FLIP_SERVO_PIN 13

// CONSTANTS

#define MARKER_ID 401
#define ROOM_NUMBER 1120

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

  pinMode(REED1, INPUT_PULLUP);
  pinMode(REED2, INPUT_PULLUP);
  pinMode(REED3, INPUT_PULLUP);
  pinMode(LEFT_LIMIT, INPUT_PULLUP);
  pinMode(RIGHT_LIMIT, INPUT_PULLUP);
  pinMode(DUTY_PIN, INPUT_PULLUP);

  CLAW.attach(CLAW_SERVO_PIN);
  FLIP.attach(FLIP_SERVO_PIN);
  CLAW.write(0);

  Enes100.begin("Oscar", DATA, MARKER_ID, ROOM_NUMBER, TX, RX);
  Enes100.println("Connected");
  Serial.println("Connected");
}

void loop() {
  stage01();
  delay(5000);
}

