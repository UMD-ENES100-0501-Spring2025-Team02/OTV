/*
 * Written by Thomas Kimberlin
 */

#ifndef OBSTACLE_NAVIGATION_H
#define OBSTACLE_NAVIGATION_H

#define OB_MOVE_SPEED 200
#define OB_TURN_SPEED 140
#define OB_T_TOLERANCE 0.05

// The following values should be determined using the ArUdo marker, OTV, and vision system. For positions other than the MID_OB_* and SHIFT, position the OTV such that it is in the position where the limit should trigger and read the coordinates. For MID_OB_* and SHIFT, place the center of the ArUco at the bottom and top of the middle obstacle position to obtain MID_OB_*, then estimate a SHIFT that would increase MID_OB_LOW to a coordinate right below MID_OB_HIGH and vice versa.
#define TOP_OB 1.9

#define MID_OB_HIGH 1.2
#define MID_OB_LOW 0.9
#define SHIFT 0.25

#define BOT_OB 0.25

#define LEVEL02 1.85
#define LOG_X 3.05

// These two macros are DIFFERENT!!! GO_TO_SHIFT moves the go_to position up or down depending on what direction the OTV must go to get to the go_to position. GO_TO_TOLERANCE is used to ensure the OTV gets to the go_to position.
#define GO_TO_SHIFT 0.3
#define GO_TO_TOLERANCE 0.1

// Used for backing up when an obstacle is hit while in obstacle_protocol()
#define PROTOCOL_DELAY 250

void stage03();
void align_to_obstacles();
void obstacle_navigation();
void obstacle_protocol(float stage, float *go_to);
int bump_sensor();

#endif OBSTACLE_NAVIGATION_H
