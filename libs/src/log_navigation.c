#include "log_navigation.h"

void stage04(){ // Add visibility checks
    
    delay(1000);
    
    visibility_check(Y);
    
    vision_print_coordinates();
        Enes100.println("LOG_Y");
        Enes100.print(LOG_Y);
    
    if (otv.y > LOG_Y){
        turn_to(L_NAV_SPEED, -PI/2, L_T_TOLERANCE, NAV);
        move(L_NAV_SPEED, FORWARD, NAV);
        while (otv.y > LOG_Y || otv.y == -1){
            if (visibility_check(Y)){
                move(L_NAV_SPEED, FORWARD, NAV);
            }
        }
    }
    
    visibility_check(THETA);
    turn_to(L_NAV_SPEED, 0, L_T_TOLERANCE, NAV);
    move(L_FINISH_SPEED, FORWARD, NAV);
    while (otv.x < GOAL_X || otv.x == -1){
        get_coordinates(X);
    }
    Enes100.print("FINISHED!!!");
    stop_drive();
}
