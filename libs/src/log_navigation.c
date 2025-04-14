#include "log_navigation.h"

void stage05(){
    get_coordinates(0, 0, ALL);
    float up = otv.x + L_BOUND_TOLERANCE;
    float down = otv.x - L_BOUND_TOLERANCE;
    
    if (otv.y > LOG_Y){
        turn_to(L_NAV_SPEED, -PI/2, L_T_TOLERANCE, NAV, 0, 0);
        move(L_NAV_SPEED, FORWARD, NAV);
        movement_correction(L_NAV_SPEED, X, up, down, L_NAV_LANE, -PI/2, NAV, TRUE, L_T_TOLERANCE, 0, 0);
        while (otv.y > LOG_Y){
            movement_correction(L_NAV_SPEED, X, up, down, L_NAV_LANE, -PI/2, NAV, FALSE, L_T_TOLERANCE, 0, 0);
        }
    }
    
    turn_to(L_NAV_SPEED, 0, L_T_TOLERANCE, NAV, 0, 0);
    move(L_FINISH_SPEED, FORWARD, NAV);
    while (otv.x < GOAL_X){
        get_coordinates(0, 0, X);
    }
    stop_drive();
}
