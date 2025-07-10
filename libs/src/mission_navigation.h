/*
 * Written by Thomas Kimberlin
 */

#ifndef MISSION_NAVIGATION_H
#define MISSION_NAVIGATION_H

#define M_NAV_SPEED 170
#define ALIGN_SPEED_OFFSET -30

#define M_T_TOLERANCE 0.2
#define ALIGN_T_TOLERANCE 0.05

// These values should be determined by taking the ArUco marker and recording the coordinates the vision system displays when the ArUco is placed directly on the mission sites
#define MIS_UX 0.3
#define MIS_DX 0.3
#define MIS_UY 1.55
#define MIS_DY 0.44

// This value should be determined through measuring the length from the center of the ArUco to the end of the extended claw and through testing
#define STOP_BEF_MIS 0.57

// These values should be determined through testing
#define ALIGN_T_DELAY 250
#define SURROUND_DELAY 1750
#define MIS_LOCO_DELAY_OFFSET 1250

void stage01();
void orient_towards_mission(coordinate *mission);
void move_to_mission(coordinate *mission);
void align_claw(coordinate *mission);
void surround_pylon(coordinate *mission);

#endif MISSION_NAVIGATION_H
