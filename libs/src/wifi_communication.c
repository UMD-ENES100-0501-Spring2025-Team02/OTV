#include "wifi_communication.h"

void get_coordinates(int pick){
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
}

int visibility_check(int pick){
    get_coordinates(pick);
    while (!Enes100.isVisible()){
        stop_drive();
        get_coordinates(pick);
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

int compare_angles(coordinate origin, coordinate *compare, float tolerance, int *origin_t_greater){
    visibility_check(ALL);
        vision_print_coordinates();

        Enes100.print("origin_theta");
        Enes100.println(origin.theta);
    
    compare->theta = calculate_angle(origin, compare);
    
        Enes100.print("compare_theta");
        Enes100.println(compare->theta);
    
    float diff = otv.theta - compare->theta;
    
        Enes100.print("diff");
        Enes100.println(diff);

    // Normalize the difference to [-π, π] for proper comparison
    while (diff < -PI) diff += 2 * PI;
    while (diff > PI) diff -= 2 * PI;

    // Determine which angle is greater
    *origin_t_greater = (diff > 0) ? TRUE : FALSE;
    
        Enes100.print("origin_t_greater");
        Enes100.println(*origin_t_greater);

    // Check if angles are within the tolerance
    return (fabsf(diff) <= tolerance) ? 1 : 0;
}
