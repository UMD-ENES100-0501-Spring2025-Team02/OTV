/*
 * Written by Thomas Kimberlin
 */

#ifndef MOTOR_CONTROLS_H
#define MOTOR_CONTROLS_H

/*
 * The macro MIS indicates the front of the OTV is located at the claw and is used until the Data Extraction mission is complete. The macro NAV indicates the front
 * of the OTV is located at the limit switches and is used throughout obstacle and log navigation.
 */
#define MIS 0
#define NAV 1

#define FORWARD 2
#define BACKWARD 3
#define RIGHT 4
#define LEFT 5

#define PWM_OFFSET 40 // Alter based on physical motor speeds

void move(int pwm, int dir, int face);
void turn(int pwm, int dir, int face);
void stop_drive();

#endif MOTOR_CONTROLS_H
