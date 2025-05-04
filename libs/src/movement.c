#include "movement.h"

void turn_to(int pwm, float target_theta, float tolerance, int face){
    float angle_diff;
    int turn_dir;
    
    visibility_check(THETA);
    
    if (face == NAV){
        target_theta += PI;
    }
    change_interval(&target_theta); // Potential bug
    
    angle_diff = target_theta - otv.theta;
    
    if (angle_diff > PI){
        angle_diff -= 2 * PI;
    } else if (angle_diff < -PI){
        angle_diff += 2 * PI;
    }
    
    turn_dir = angle_diff < 0 ? RIGHT : LEFT;
    if (face == NAV){
        turn_dir = turn_dir == RIGHT ? LEFT : RIGHT;
    }
    
    turn(pwm, turn_dir, face);
    
    while (abs(otv.theta - target_theta) > tolerance){
        if (visibility_check(THETA)) {
            turn(pwm, turn_dir, face);
        }
    }
    
    stop_drive();
}
