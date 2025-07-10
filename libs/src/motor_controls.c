/*
 * Written by Thomas Kimberlin
 */

#include "motor_controls.h"

void move(int pwm, int dir, int face){
    if (face == MIS && dir == FORWARD || face == NAV && dir == BACKWARD) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    }
}

void turn(int pwm, int dir, int face){
    if (face == MIS && dir == RIGHT || face == NAV && dir == LEFT){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    }
}

void stop_drive(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}
