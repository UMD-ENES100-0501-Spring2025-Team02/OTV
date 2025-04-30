#include "obstacle_navigation.h"

void stage03(){
    rotate_to_obstacles();
    obstacle_navigation();
}

void rotate_to_obstacles(){
    turn_to(OB_NAV_SPEED, 0, OB_T_TOLERANCE, NAV, 0, 0);
}

void obstacle_navigation(){
    float up = otv.y + OB_T_TOLERANCE;
    float right = otv.x + OB_T_TOLERANCE;
    float down = otv.y - OB_T_TOLERANCE;
    float left = otv.x - OB_T_TOLERANCE;
    float go_to = -1;
    float angle;
    float sensor;
    
    move(OB_NAV_SPEED, FORWARD, NAV);
    movement_correction(OB_NAV_SPEED, Y, up, down, OB_NAV_LANE, 0, NAV, TRUE, OB_T_TOLERANCE, 0, 0);
    while (otv.x < STAGE1){
        movement_correction(OB_NAV_SPEED, Y, up, down, OB_NAV_LANE, 0, NAV, FALSE, OB_T_TOLERANCE, 0, 0);
        
        
    }
}


int bump_sensor(){
    return digitalRead(LEFTlimit) == LOW || digitalRead(RIGHTlimit) == LOW ? TRUE : FALSE;
}
