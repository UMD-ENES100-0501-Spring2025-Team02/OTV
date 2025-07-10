/*
 * Written by Thomas Kimberlin
 */

#include "obstacle_navigation.h"

void stage03(){
    // EDIT: Due to the detatching of the flipping servo in filpSilo() in stage02(), this most likely does nothing other than add additional delay
    FLIP.write(0);
    delay(2000);
    
    align_to_obstacles();
    obstacle_navigation();
    return;
}

// The OTV tends to not align correctly initially, so an additional alignment is added after moving a certain amount in order to correct the misalignment
void align_to_obstacles(){
    turn_to(OB_TURN_SPEED, 0, OB_T_TOLERANCE, NAV);
    move(255, FORWARD, NAV);
    delay(1500);
    stop_drive();
    turn_to(OB_TURN_SPEED, 0, OB_T_TOLERANCE, NAV);
}

/*
 * The approach to the obstacles is split into two levels, the first level for the first column of obstacles, and the second level for the second column.
 * At the first level, if the OTV hits an obstacle, it will enter obstacle_protocol() which checks each position until the OTV passes the level and saves the
 * position of the last obstacle encountered to be used in the level two code. Since the OTV can go over the traversable obstacle, the approach to both levels is
 * the same, with the exception of when the OTV enters the protocol on the first level. In that case, after passing the first level, the OTV will go straight back
 * to the saved position to pass the second level of obstacles. The LOG_X macro is the x position of the OTV such that it is in position to do log navigation, not
 * the log's x physical position.
 *
 * EDIT: Thomas Kimberlin realizes that this code is quite messy and could have been broken down into more function. Additionally, he potentially found unnecessary
 * code based on the logic of the strategy. However, during testing, no glaring bugs were encountered in this code like in other parts of the project code, so nothing
 * was done. Thomas believes that if he had more time, he would have reformatted the code, but since the class is over, he does not want to alter the code and risk
 * introducing more bugs that were not present.
 */
void obstacle_navigation(){
    float angle, go_to;
    int obstacle = FALSE;
    
    visibility_check(ALL);
    
    // Level 1
    while (otv.x < LEVEL02){
        if (visibility_check(XY)){
            move(OB_MOVE_SPEED, FORWARD, NAV);
            if (bump_sensor()){
                // Position of last obstacle hit is saved in go_to
                go_to = otv.y;
                obstacle = TRUE;
                obstacle_protocol(LEVEL02, &go_to);
                break;
            }
        }
    }
    
    // Level 2
    if (obstacle){
        // Calculates direction to move to arrive at go_to
        angle = otv.y > go_to ? -PI/2 : PI/2;
        go_to = angle == PI/2 ? go_to + GO_TO_SHIFT : go_to - GO_TO_SHIFT;
        
        // Moves to go_to and passes level two obstacles
        turn_to(OB_TURN_SPEED, angle, OB_T_TOLERANCE, NAV);
        while (otv.y >= go_to + GO_TO_TOLERANCE || otv.y <= go_to - GO_TO_TOLERANCE){
            if (visibility_check(Y)){
                move(OB_MOVE_SPEED, FORWARD, NAV);
            }
        }
        turn_to(OB_TURN_SPEED, 0, OB_T_TOLERANCE, NAV);
        while (otv.x < LOG_X){
            if (visibility_check(X)){
                move(OB_MOVE_SPEED, FORWARD, NAV);
            }
        }
    } else {
        // Repeats level one approach but does not save go_to since it is not required after passing level two obstacles
        while (otv.x < LOG_X){
            if (visibility_check(XY)){
                move(OB_MOVE_SPEED, FORWARD, NAV);
                if (bump_sensor()){
                    obstacle_protocol(LOG_X, &go_to);
                    break;
                }
            }
        }
    }
    stop_drive();
}

void obstacle_protocol(float stage, float *go_to){
    float angle, mid_ob_low, mid_ob_high;
    int i, passed = FALSE;
    
    visibility_check(ALL);
    if (otv.y > 1){
        angle = -PI/2;
        mid_ob_low = MID_OB_LOW;
        mid_ob_high = MID_OB_HIGH - SHIFT;
    } else {
        angle = PI/2;
        mid_ob_low = MID_OB_LOW + SHIFT;
        mid_ob_high = MID_OB_HIGH;
    }
    
    // Assumes there are two spots for obstacles remaining
    for (i = 0; i < 2 && passed == FALSE; ++i){
        move(OB_MOVE_SPEED, BACKWARD, NAV);
        delay(PROTOCOL_DELAY);
        turn_to(OB_TURN_SPEED, angle, OB_T_TOLERANCE, NAV);
        
        // Position OTV must travel to changes every loop
        switch (i){
            case 0:
                while (otv.y <= mid_ob_low || otv.y >= mid_ob_high){
                    if (visibility_check(Y)){
                        move(OB_MOVE_SPEED, FORWARD, NAV);
                    }
                }
                break;
            case 1:
                while (otv.y <= TOP_OB && otv.y >= BOT_OB){
                    if (visibility_check(Y)){
                        move(OB_MOVE_SPEED, FORWARD, NAV);
                    }
                }
                break;
            default:
                break;
        }
        turn_to(OB_TURN_SPEED, 0, OB_T_TOLERANCE, NAV);
        
        passed = TRUE;
        visibility_check(ALL);
        while (otv.x < stage){
            if (visibility_check(X)){
                move(OB_MOVE_SPEED, FORWARD, NAV);
                if (bump_sensor()){
                    *go_to = otv.y;
                    passed = FALSE;
                    break;
                }
            }
        }
    }
    
    // Ensures the OTV goes past the current level of obstacles if it did not in the loop. EDIT: This check may not have been necessary.
    if (!passed){
        turn_to(OB_TURN_SPEED, 0, OB_T_TOLERANCE, NAV);
        while (otv.x < stage){
            if (visibility_check(X)){
                move(OB_MOVE_SPEED, FORWARD, NAV);
            }
        }
    }
}

int bump_sensor(){
    int check = digitalRead(LEFT_LIMIT) == LOW || digitalRead(RIGHT_LIMIT) == LOW ? TRUE : FALSE;
    
    if (check){
        move(200, BACKWARD, NAV);
        delay(750);
        stop_drive();
    }
    
    return check;
}
