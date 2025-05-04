#include "obstacle_navigation.h"

void stage03(){
    align_to_obstacles();
    obstacle_navigation();
}

void align_to_obstacles(){
    turn_to(OB_NAV_SPEED, 0, OB_T_TOLERANCE, NAV);
}

void obstacle_navigation(){
    float angle, go_to;
    int obstacle = FALSE;
    
    visibility_check(ALL);
    while (otv.x < STAGE2){
        if (visibility_check(XY)){
            move(OB_NAV_SPEED, FORWARD, NAV);
            if (bump_sensor()){
                go_to = otv.y;
                obstacle = TRUE;
                obstacle_protocol(STAGE2, &go_to);
                break;
            }
        }
    }
    
    if (obstacle){
        angle = otv.y > go_to ? -PI/2 : PI/2;
        go_to = angle == PI/2 ? go_to + SHIFT : go_to - SHIFT;
        turn_to(OB_NAV_SPEED, angle, OB_T_TOLERANCE, NAV);
        //move(OB_NAV_SPEED, FORWARD, NAV);
        while (otv.y >= go_to + GO_TO_TOLERANCE || otv.y <= go_to - GO_TO_TOLERANCE){
            if (visibility_check(Y)){
                move(OB_NAV_SPEED, FORWARD, NAV);
            }
        }
        turn_to(OB_NAV_SPEED, 0, OB_T_TOLERANCE, NAV);
        while (otv.x < LOG_X){
            if (visibility_check(X)){
                move(OB_NAV_SPEED, FORWARD, NAV);
            }
        }
    } else {
        obstacle_protocol(LOG_X, &go_to);
    }
    stop_drive();
}

void obstacle_protocol(float stage, float *go_to){
    float angle, mid_ob_low, mid_ob_high;
    int i, passed = FALSE;
    
    visibility_check(ALL);
    if (otv.y > 1){
        angle = -PI/2;
        mid_ob_low = MID_OB_LOW - SHIFT;
        mid_ob_high = MID_OB_HIGH - SHIFT;
    } else {
        angle = PI/2;
        mid_ob_low = MID_OB_LOW + SHIFT;
        mid_ob_high = MID_OB_HIGH + SHIFT;
    }
    
    for (i = 0; i < 2 && passed == FALSE; ++i){
        move(OB_NAV_SPEED, BACKWARD, NAV);
        delay(PROTOCOL_DELAY);
        turn_to(OB_NAV_SPEED, angle, OB_T_TOLERANCE, NAV);
        
        //move(OB_NAV_SPEED, FORWARD, NAV);
        switch (i){
            case 1:
                while (otv.y <= mid_ob_low || otv.y >= mid_ob_high){
                    if (visibility_check(Y)){
                        move(OB_NAV_SPEED, FORWARD, NAV);
                    }
                }
                break;
            case 2:
                while (otv.y <= TOP_OB && otv.y >= BOT_OB){
                    if (visibility_check(Y)){
                        move(OB_NAV_SPEED, FORWARD, NAV);
                    }
                }
                break;
            default:
                break;
        }
        turn_to(OB_NAV_SPEED, 0, OB_T_TOLERANCE, NAV);
        
        //move(OB_NAV_SPEED, FORWARD, NAV);
        visibility_check(ALL);
        while (otv.x < stage){
            if (visibility_check(X)){
                move(OB_NAV_SPEED, FORWARD, NAV);
                if (bump_sensor()){
                    *go_to = otv.y;
                    passed = TRUE;
                    break;
                }
            }
        }
    }
}

int bump_sensor(){
    return digitalRead(LEFT_LIMIT) == LOW || digitalRead(RIGHT_LIMIT) == LOW ? TRUE : FALSE;
}
