/*
 * Written by Thomas Kimberlin
 */

#include "log_navigation.h"

void stage04(){
    visibility_check(Y);
    
    // Ensures OTV is facing log before heading to the goal zone
    if (otv.y > LOG_Y){
        turn_to(L_NAV_SPEED, -PI/2, L_T_TOLERANCE, NAV);
        move(L_NAV_SPEED, FORWARD, NAV);
        while (otv.y > LOG_Y || otv.y == -1){
            if (visibility_check(Y)){
                move(L_NAV_SPEED, FORWARD, NAV);
            }
        }
    }
    
    // Angle check
    visibility_check(THETA);
    turn_to(L_NAV_SPEED, 0, L_T_TOLERANCE, NAV);
    
    // Completes mission by going over the log into the goal zone
    move(L_FINISH_SPEED, FORWARD, NAV);
    
    /*
     * The vision system returns -1 for x and y coordinates when the OTV is not visibility, as stated in mission_navigation.c, but also when the OTV
     * is not in the arena. So there is an additional check here for that coordinate in order to ensure the OTV is fully in the goal zone. However, be careful
     * since the OTV could perpetually run after reaching the goal zone in some cases, so make sure to catch it on the other side.
     */
    while (otv.x < GOAL_X || otv.x == -1){
        get_coordinates(X);
    }
    Enes100.print("FINISHED!!!");
    stop_drive();
    return;
}
