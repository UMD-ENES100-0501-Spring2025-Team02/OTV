/*
 * Written by Thomas Kimberlin
 */

#ifndef LOG_NAVIGATION_H
#define LOG_NAVIGATION_H

#define L_NAV_SPEED 200
#define L_FINISH_SPEED 255

#define L_T_TOLERANCE 0.2

// These values should be determined using the ArUco and the expected OTV positioning when these limits should trigger.
#define LOG_Y 0.3
#define GOAL_X 4

void stage04();

#endif LOG_NAVIGATION_H
