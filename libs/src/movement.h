#ifndef MOVEMENT_H
#define MOVEMENT_H

#define MIS 0
#define NAV 1

void move(int pwm, int dir, int face);
void turn(int pwm, int dir, int face);
void stop_drive();
void turn_to(float target_theta, int face);


int move_int(int interval);
int move_point(int point);


#endif MOVEMENT_H
