#include "movement.h"

void move(int pwm, int dir, int face){
    if (face == MIS && dir == FORWARD || face == NAV && dir == BACKWARD) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    }
}

void turn(int pwm, int dir, int face){
    if (face == MIS && dir == RIGHT || face == NAV && dir == LEFT){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, pwm - PWM_OFFSET);
        analogWrite(ENB, pwm);
    }
}

void stop_drive(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

void turn_to(int pwm, float target_theta, float tolerance, int face, float v_r, float v_theta){
    float angle_diff;
    int turn_dir;
    
    get_coordinates(v_r, v_theta, THETA);
    
    if (face == NAV){
        target_theta += PI;
    }
    
    while (target_theta >= 2 * PI){
        target_theta -= 2 * PI;
    }
    
    angle_diff = target_theta - otv.theta;
    
    if (angle_diff > PI){
        angle_diff -= 2 * PI;
    } else if {
        angle_diff =+ 2 * PI;
    }
    
    turn_dir = angle_diff < 0 ? RIGHT : LEFT;
    turn(pwm, turn_dir, face);
    
    while (abs(otv_theta - target_theta) > tolerance){
        get_coordinates(v_r, v_theta, THETA);
    }
    
    stop_drive();
}

void movement_correction(int pwm, int axis, float ur, float dl, float lane, float goal_theta, int face, int repeat, float tolerance, float v_r, float v_theta){
    static float sur = ur;
    static float sdl = dl;
    static int dir_fact = axis == X ? (goal >= 0 ? 1 : -1) : (goal >= 0 ? -1 : 1);
    
    if (repeat){
        sur = ur;
        sdl = dl;
        dir_fact = axis == X ? (goal >= 0 ? 1 : -1) : (goal >= 0 ? -1 : 1);
    }
    
    get_coordinates(v_r, v_theta, XY);
    
    if (axis == X){
        if (otv.x >= sur){
            turn_to(pwm, goal + dir_fact * tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x >= sur - lane){
                get_coordinates(v_r, v_theta, X);
            }
        } else {
            turn_to(pwm, goal - dir_fact * tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x <= sdl + lane){
                get_coordinates(v_r, v_theta, X);
            }
        }
    } else if (axis == Y){
        if (otv.y >= sur){
            turn_to(pwm, goal + dir_fact * tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x >= sur - lane){
                get_coordinates(v_r, v_theta, Y);
            }
        } else {
            turn_to(pwm, goal - dir_fact * tolerance, face, v_r, v_theta);
            move(pwm, FORWARD, face);
            while (otv.x <= sdl + lane){
                get_coordinates(v_r, v_theta, Y);
            }
        }
    }
    
    turn_to(pwm, goal, face, v_r, v_theta);
    move(pwm, FORWARD, face);
}
