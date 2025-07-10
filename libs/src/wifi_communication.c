/*
 * Written by Thomas Kimberlin
 */

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

// Due to the unreliability of the ENES100 Vision Systems, this function is used to negate unpredictable behavior by the OTV due to the inaccuracy of the vision system. This function is used to obtain the coordinates of the OTV rather than only calling get_coordinates() to ensure the correct coordinates are obtained. If the OTV is not visible to the vision system, it will stop in order for the vision system to locate it. However, if the ArUco marker is still not visible, the OTV will stay stationary. In that case, the OTV must be altered so that the ArUco marker can be located more consistently.
int visibility_check(int pick){
    get_coordinates(pick);
    while (!Enes100.isVisible()){
        stop_drive();
        get_coordinates(pick);
        delay(1);
    }
    get_coordinates(pick);
    delay(1);
    
    // This function returns TRUE such that it can be used in if statements that continue the desired movement if the OTV stops due to invisibility. EDIT: This function may not need to be called with if statements to continue the desired movement, rather, the desired movement can just be called after visibility_check().
    return TRUE;
}

// The following three functions can be inserted throughout the code for testing and debugging
void serial_print_coordinates(){
    Serial.print("X = ");
    Serial.println(otv.x);
    Serial.print("Y = ");
    Serial.println(otv.y);
    Serial.print("Theta = ");
    Serial.println(otv.theta);
    Serial.print("");
}

// These coordinates will show up on the ENES100 Vision System
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

// This function is used to reorient the OTV towards the pylon
int compare_angles(coordinate origin, coordinate *compare, float tolerance, int *origin_t_greater){
    visibility_check(ALL);
    
    compare->theta = calculate_angle(origin, compare);
    
    float diff = otv.theta - compare->theta;

    // Changes interval of diff to [-PI, PI]
    while (diff < -PI) diff += 2 * PI;
    while (diff > PI) diff -= 2 * PI;

    // Determines which angle is greater
    *origin_t_greater = (diff > 0) ? TRUE : FALSE;

    // Checks if angles are within the given tolerance. The function fabsf() returns the absolute value of a floating point number.
    return (fabsf(diff) <= tolerance) ? TRUE : FALSE;
}
