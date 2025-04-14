#include "mission_navigation.h"

void stage01(){
    coordinate mission;
    
    orient_towards_mission(&mission);
    move_to_mission(&mission);
}

void orient_towards_mission(coordinate *mission){
    get_coordinates(0, 0, ALL);
    mission->x = MIS_X;
    mission->y = (otv.y < 1) ? MIS_UY : MIS_DY;
    mission->theta = (otv.y < 1) ? PI/2 : -PI/2;
    turn_to(M_NAV_SPEED, mission->theta, M_T_TOLERANCE, MIS, 0, 0);
}

void move_to_mission(coordinate *mission){
    move(M_NAV_SPEED, FORWARD, MIS);
    movement_correction_mission(mission);
    stop_drive();
}

void movement_correction_mission(coordinate *mission){
    movement_correction(M_NAV_SPEED, X, M_R_BOUND, M_L_BOUND, M_NAV_LANE, mission->theta, MIS, TRUE, M_T_TOLERANCE, 0, 0);
    if (mission->y == MIS_UY){
        while (otv.y < MIS_UY - STOP_BEF_MIS){
            movement_correction(M_NAV_SPEED, X, M_R_BOUND, M_L_BOUND, M_NAV_LANE, mission->theta, MIS, FALSE, M_T_TOLERANCE, 0, 0);
        }
    } else {
        while (otv.y > MIS_DY + STOP_BEF_MIS){
            movement_correction(M_NAV_SPEED, X, M_R_BOUND, M_L_BOUND, M_NAV_LANE, mission->theta, MIS, FALSE, M_T_TOLERANCE, 0, 0);
        }
    }
}
