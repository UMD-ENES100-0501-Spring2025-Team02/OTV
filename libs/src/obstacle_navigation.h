#ifndef OBSTACLE_NAVIGATION_H
#define OBSTACLE_NAVIGATION_H

#define TOP_OB 1.4
#define MID_OB_HIGH 1.0
#define MID_OB_LOW 0.9
#define SHIFT 0.3
#define BOT_OB 0.6

#define GO_TO_TOLERANCE 0.1

#define STAGE2 2
#define LOG_X 3.5

#define OB_NAV_SPEED 200
#define OB_T_TOLERANCE 0.2

#define PROTOCOL_DELAY 250

void stage03();
void align_to_obstacles();
void obstacle_navigation();
void obstacle_protocol(float stage, float *go_to);
int bump_sensor();

#endif OBSTACLE_NAVIGATION_H
