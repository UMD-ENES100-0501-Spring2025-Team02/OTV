#include "movement.h"

void turn_to(int pwm, float target_theta, float tolerance, int face, float v_r, float v_theta){
    float angle_diff;
    int turn_dir;
    
    get_coordinates(v_r, v_theta, THETA);
    
    while (target_theta < 0){
        target_theta += 2 * PI;
    }
    
    if (face == NAV){
        target_theta += PI;
    }
    
    while (target_theta >= 2 * PI){
        target_theta -= 2 * PI;
    }
    
    //Enes100.println("TARGET THETA CHECK ");
    //Enes100.print(target_theta);
    delay(1000);
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
    
    while (abs(otv.theta - target_theta) > tolerance){ // Potential -1 bug
        get_coordinates(v_r, v_theta, THETA);
        //vision_print_coordinates();
        if (visibility_check(0, 0, THETA)) {
            turn(pwm, turn_dir, face);
        }
    }
    
    stop_drive();
}

void movement_correction(int pwm, int axis, float ur, float dl, float lane, float goal_theta, int face, int repeat, float tolerance, float v_r, float v_theta){
    static float sur = ur;
    static float sdl = dl;
    static int dir_fact = axis == X ? (goal_theta >= 0 ? 1 : -1) : (goal_theta >= 0 ? -1 : 1);
    
    if (repeat){
        sur = ur;
        sdl = dl;
        dir_fact = axis == X ? (goal_theta >= 0 ? 1 : -1) : (goal_theta >= 0 ? -1 : 1);
    }
    
    
    get_coordinates(v_r, v_theta, XY);
    
    if (axis == X){
        if (otv.x >= sur){
            Enes100.print("Check 3");
            turn_to(pwm, goal_theta + dir_fact * ADJUST, tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x >= sur - lane || otv.x == -1){
                get_coordinates(v_r, v_theta, X);
            }
        } else if (otv.x <= sdl) {
            Enes100.print("Check 4");
            turn_to(pwm, goal_theta - dir_fact * ADJUST, tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x <= sdl + lane || otv.x == -1){
                get_coordinates(v_r, v_theta, X);
            }
        }
    } else if (axis == Y){
        if (otv.y >= sur){
            turn_to(pwm, goal_theta + dir_fact * ADJUST, tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x >= sur - lane || otv.x == -1){
                get_coordinates(v_r, v_theta, Y);
            }
        } else if (otv.y >= sdl){
            turn_to(pwm, goal_theta - dir_fact * ADJUST, tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x <= sdl + lane || otv.x == -1){
                get_coordinates(v_r, v_theta, Y);
            }
        }
    }
    
    Enes100.print("Check 6");
    turn_to(pwm, goal_theta, tolerance, face, v_r, v_theta);
    Enes100.print("Check 7");
    move(pwm, FORWARD, face);
}
