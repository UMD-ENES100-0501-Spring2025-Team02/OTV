#ifndef MOVEMENT_H
#define MOVEMENT_H

#define MIS 0
#define NAV 1
#define FORWARD 2
#define BACKWARD 3
#define RIGHT 4
#define LEFT 5
#define PWM_OFFSET 3

#define TRUE 1
#define FALSE 0

void move(int pwm, int dir, int face);
void turn(int pwm, int dir, int face);
void stop_drive();
void turn_to(int pwm, float target_theta, float tolerance, int face, float v_r, float v_theta);
void movement_correction(int pwm, int axis, float ur, float dl, float lane, float goal_theta, int face, int repeat, float tolerance, float v_r, float v_theta);

#endif MOVEMENT_H
