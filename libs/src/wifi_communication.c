#include "wifi_communication.h"

void get_coordinates(float r, float theta, int pick){
    switch (pick){
        case XY:
            otv.y = Enes100.getY();
        case X:
            otv.x = Enes100.getX();
            break;
        case Y:
            otv.y = Enes100.getY();
            break;
        case THETA:
            otv.theta = Enes100.getTheta();
            break;
        default:
            otv.x = Enes100.getX();
            otv.y = Enes100.getY();
            otv.theta = Enes100.getTheta();
            break;
    }
    
    change_interval(&otv.theta);
    virtual_reference(&otv, r, theta);
}

int visibility_check(float v_r, float v_theta, int pick){
    while (!Enes100.isVisible()){
        stop_drive();
        get_coordinates(v_r, v_theta, pick);
    }
    return TRUE;
}

void serial_print_coordinates(){
    Serial.print("X = ");
    Serial.println(otv.x);
    Serial.print("Y = ");
    Serial.println(otv.y);
    Serial.print("Theta = ");
    Serial.println(otv.theta);
    Serial.print("");
}

void vision_print_coordinates(){
    Enes100.print("X = ");
    Enes100.println(otv.x);
    Enes100.print("Y = ");
    Enes100.println(otv.y);
    Enes100.print("Theta = ");
    Enes100.println(otv.theta);
    Enes100.print("");
}

void print_coordinates(){
    serial_print_coordinates();
    vision_print_coordinates();
}

int compare_angles(coordinate otv, coordinate *compare, float v_r, float v_theta, float tolerance, int *otv_t_greater){
    get_coordinates(v_r, v_theta, ALL); // Add visibility check
    vision_print_coordinates();
    visibility_check(v_r, v_theta, ALL);

    float angle1 = otv.theta;
    Enes100.println("OTV Theta");
    Enes100.print(angle1);
    get_coordinates(0, 0, ALL);
    visibility_check(v_r, v_theta, ALL);
    float angle3 = angle_with_x_axis(otv, compare);
    Enes100.println("CLAW to PYLON Theta");
    Enes100.print(angle3);
    
    *otv_t_greater = angle1 > angle3 ? 1 : 0;
    Enes100.println("otv_t_greater");
    Enes100.print(*otv_t_greater);

    float diff = fabs(angle1 - angle3);
    Enes100.println("diff");
    Enes100.print(diff);
    float angle_between = fmin(diff, 2 * PI - diff);
    Enes100.println("angle_between");
    Enes100.print(angle_between);

    delay(7500);
    return fabs(angle_between) <= tolerance ? 1 : 0;
}
