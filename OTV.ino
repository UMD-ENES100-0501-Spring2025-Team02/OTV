#include "libs/OTV.h"

// PIN ASSIGNMENTS

#define IN1 13
#define IN2 12
#define ENA 11

#define IN3 10
#define IN4 9
#define ENB 8

#define TX 1
#define RX 0

#define MOTOR_1 1
#define MOTOR_2 2

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

}

void loop() {

}
