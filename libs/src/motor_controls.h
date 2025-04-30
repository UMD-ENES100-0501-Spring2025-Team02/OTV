#ifndef MOTOR_CONTROLS_H
#define MOTOR_CONTROLS_H

#define MIS 0
#define NAV 1
#define FORWARD 2
#define BACKWARD 3
#define RIGHT 4
#define LEFT 5
#define PWM_OFFSET 3

void move(int pwm, int dir, int face);
void turn(int pwm, int dir, int face);
void stop_drive();

#endif MOTOR_CONTROLS_H
