#ifndef MISSION_NAVIGATION_H
#define MISSION_NAVIGATION_H

#define M_NAV_SPEED 170 // Depends on wheels of OTV so might need to be changed 125

#define MIS_X 0.3
#define MIS_UY 1.55 // Theo
#define MIS_DY 0.44 // Theo
#define STOP_BEF_MIS 0.55 // Depends on physical constraints

#define M_T_TOLERANCE 0.2 // Changed
#define ALIGN_T_TOLERANCE 0.08

#define ALIGN_T_DELAY 250
#define S1_S2_DELAY 2000

void stage01();
void orient_towards_mission(coordinate *mission);
void move_to_mission(coordinate *mission);
void align_claw(coordinate *mission);
void surround_pylon();

#endif MISSION_NAVIGATION_H
