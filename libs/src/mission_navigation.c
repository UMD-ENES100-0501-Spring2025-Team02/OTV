/*
 * Written by Thomas Kimberlin
 */

#include "mission_navigation.h"

void stage01(){
    coordinate mission;
    
    delay(1000);
    
    orient_towards_mission(&mission);
    
    // The general strategy to surround the pylon with the claw is to move towards the pylon up to a certain point, realign so the claw faces the pylon, then move towards the pylon for a certain amount of time. EDIT: This strategy proved to be hit or miss due to the hard coded times after realignment to move forward. A better strategy would be to have a sensor below the claw to determine when the pylon is in the correct position and stop at that point.
    move_to_mission(&mission);
    align_claw(&mission);
    surround_pylon(&mission);
    return;
}

void orient_towards_mission(coordinate *mission){
    visibility_check(ALL);
    
    mission->x = (otv.y < 1) ? MIS_UX : MIS_DX;
    mission->y = (otv.y < 1) ? MIS_UY : MIS_DY;
    mission->theta = (otv.y < 1) ? PI/2 : -PI/2;
    
    turn_to(M_NAV_SPEED, mission->theta, M_T_TOLERANCE, MIS);
}

void move_to_mission(coordinate *mission){
    move(M_NAV_SPEED, FORWARD, MIS);
    
    visibility_check(Y);
    if (mission->y > 1){
        while (otv.y < MIS_UY - STOP_BEF_MIS){
            if (visibility_check(ALL)) {
                move(M_NAV_SPEED, FORWARD, MIS);
            }
        }
    } else {
        // The vision system returns -1 for x and y coordinates when the OTV is not visibility, so there is an additional check here for that coordinate
        while (otv.y > MIS_DY + STOP_BEF_MIS || otv.y == -1){
            if (visibility_check(ALL)) {
                move(M_NAV_SPEED, FORWARD, MIS);
            }
        }
    }
    stop_drive();
}

void align_claw(coordinate *mission){
    int otv_t_greater;
    
    // Unlike other situations where we want to turn to a specific angle, this code causes the OTV to make incremental rotations with breaks in between in order to get accurate calculations.
    while (!compare_angles(otv, mission, ALIGN_T_TOLERANCE, &otv_t_greater)){
        if (otv_t_greater){
            turn(M_NAV_SPEED + ALIGN_SPEED_OFFSET, RIGHT, MIS);
            delay(ALIGN_T_DELAY);
            stop_drive();
        } else {
            turn(M_NAV_SPEED + ALIGN_SPEED_OFFSET, LEFT, MIS);
            delay(ALIGN_T_DELAY);
            stop_drive();
        }
        delay(ALIGN_T_DELAY);
    }
}

void surround_pylon(coordinate *mission){
    move(M_NAV_SPEED, FORWARD, MIS);
    
    // This if statement is dependent on physical conditions, allowing the OTV to move further depending on where the the pylon ended up during randomization. The statement, along with the macro MIS_LOCO_DELAY_OFFSET can be removed or altered depending on the conditions of the arena and testing.
    if (mission->y == MIS_DY) {delay(MIS_LOCO_DELAY_OFFSET);}
    
    delay(SURROUND_DELAY);
    stop_drive();
}

