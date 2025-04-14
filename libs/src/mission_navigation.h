#ifndef MISSION_NAVIGATION_H
#define MISSION_NAVIGATION_H

#define MIS_X 0.55
#define MIS_UY 1.45
#define MIS_DY 0.55
#define M_NAV_SPEED 255
#define M_T_TOLERANCE 0.05
#define M_R_BOUND 0.56
#define M_L_BOUND 0.54
#define M_NAV_LANE 0.005
#define STOP_BEF_MIS 0.05

void stage01();
void orient_towards_mission(coordinate *mission);
void move_to_mission(coordinate *mission);
void movement_correction_mission(coordinate *mission);

#endif MISSION_NAVIGATION_H
