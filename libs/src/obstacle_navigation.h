#ifndef OBSTACLE_NAVIGATION_H
#define OBSTACLE_NAVIGATION_H

#define MID_OB_LOW 0.9
#define MID_OB_HI 1.0
#define TOP_OB 1.4
#define BOT_OB 0.6
#define STAGE1 1.8
#define GO_TO_TOLERANCE 0.1
#define OB_NAV_SPEED 255
#define OB_T_TOLERANCE 0.05
#define OB_NAV_LANE 0.005

void stage03();
void rotate_to_obstacles();
void obstacle_navigation();
int bump_sensor();

#endif OBSTACLE_NAVIGATION_H
