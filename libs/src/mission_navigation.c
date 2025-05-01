#include "mission_navigation.h"

void stage01(){
    coordinate mission;
    
    delay(1000);
    orient_towards_mission(&mission);
    Enes100.print("Orient to mission complete");
    move_to_mission(&mission);
    Enes100.print("Move to mission complete");
    vision_print_coordinates();
    align_claw(&mission);
    surround_pylon();
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
    get_coordinates(0, 0, ALL);
    
    if (mission->y > 1){
        while (otv.y < MIS_UY - STOP_BEF_MIS){ // I need visibility check here
            get_coordinates(0, 0, Y);
            if (visibility_check(0, 0, ALL)) {
                move(M_NAV_SPEED, FORWARD, MIS);
            }
        }
    } else {
        while (otv.y > MIS_DY + STOP_BEF_MIS || otv.y == -1){ // I need visibility check here
            get_coordinates(0, 0, Y);
            if (visibility_check(0, 0, ALL)) {
                move(M_NAV_SPEED, FORWARD, MIS);
            }
        }
    }
    stop_drive();
}

void align_claw(coordinate *mission){
    int otv_t_greater;
    
    while (!compare_angles(otv, mission, CLAW_CENTER_R, CLAW_CENTER_T, ALIGN_T_TOLERANCE, &otv_t_greater)){
        if (otv_t_greater){
            turn(M_NAV_SPEED, LEFT, MIS);
            delay(ALIGN_T_DELAY);
            stop_drive();
        } else {
            turn(M_NAV_SPEED, RIGHT, MIS);
            delay(ALIGN_T_DELAY);
            stop_drive();
        }
    }
}

void surround_pylon(){
    move(M_NAV_SPEED, FORWARD, MIS);
    delay(S1_DELAY);
}

