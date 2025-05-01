#ifndef MISSION_NAVIGATION_H
#define MISSION_NAVIGATION_H

#define MIS_X 0.55
#define MIS_UY 1.10 // Theo
#define MIS_DY 0.90 // Theo
#define STOP_BEF_MIS 0.025 // Depends on physical constraints
#define M_NAV_SPEED 200 // Depends on wheels of OTV so might need to be changed 125
#define M_T_TOLERANCE 0.2 // Changed
#define S1_DELAY 1000
#define CLAW_CENTER_R 0.37
#define CLAW_CENTER_T 0
#define ALIGN_T_TOLERANCE 0.01
#define ALIGN_T_DELAY 250

void stage01();
void orient_towards_mission(coordinate *mission);
void move_to_mission(coordinate *mission);
void align_claw(coordinate *mission);
void surround_pylon();

#endif MISSION_NAVIGATION_H
