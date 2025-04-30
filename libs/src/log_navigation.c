#include "log_navigation.h"

void stage05(){
    delay(1000); // For testing
    while (!Enes100.isVisible()){}
    get_coordinates(0, 0, ALL);
    // float up = otv.x + L_BOUND_TOLERANCE;
    // float down = otv.x - L_BOUND_TOLERANCE;
    
    vision_print_coordinates();
    Enes100.println("LOG_Y");
    Enes100.print(LOG_Y);
    
    if (otv.y > LOG_Y){
        Enes100.print("Check 1");
        turn_to(L_NAV_SPEED, -PI/2, L_T_TOLERANCE, NAV, 0, 0);
        Enes100.print("Check 2");
        move(L_NAV_SPEED, FORWARD, NAV);
        // movement_correction(L_NAV_SPEED, X, up, down, L_NAV_LANE, -PI/2, NAV, TRUE, L_T_TOLERANCE, 0, 0);
        while (otv.y > LOG_Y || otv.y == -1){
            // movement_correction(L_NAV_SPEED, X, up, down, L_NAV_LANE, -PI/2, NAV, FALSE, L_T_TOLERANCE, 0, 0);
            get_coordinates(0, 0, Y);
        }
        Enes100.print("Check 3");
    }
    
    get_coordinates(0, 0, ALL);
    turn_to(L_NAV_SPEED, 0, L_T_TOLERANCE, NAV, 0, 0);
    Enes100.print("LOG JUMP CHECK");
    move(L_FINISH_SPEED, FORWARD, NAV);
    while (otv.x < GOAL_X){
        get_coordinates(0, 0, X);
    }
    Enes100.print("FINISH");
    stop_drive();
}
