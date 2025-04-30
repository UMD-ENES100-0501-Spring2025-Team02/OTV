#ifndef MOVEMENT_H
#define MOVEMENT_H

#define ADJUST 0.55

void turn_to(int pwm, float target_theta, float tolerance, int face, float v_r, float v_theta);
void movement_correction(int pwm, int axis, float ur, float dl, float lane, float goal_theta, int face, int repeat, float tolerance, float v_r, float v_theta);

#endif MOVEMENT_H
