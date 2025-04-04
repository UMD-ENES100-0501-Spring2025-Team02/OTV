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
    
    change_interval(&otv, STD_INTV);
    virtual_reference(&otv, r, theta);
}

void serial_print_coordinates(){
    Serial.println("X = ");
    Serial.print(otv.x);
    Serial.println("Y = ");
    Serial.print(otv.y);
    Serial.println("Theta = ");
    Serial.print(otv.theta);
    Serial.println("");
}

void vision_print_coodinates(){
    Enes100.println("X = ");
    Enes100.print(otv.x);
    Enes100.println("Y = ");
    Enes100.print(otv.y);
    Enes100.println("Theta = ");
    Enes100.print(otv.theta);
    Enes100.println("");
}

void print_coordinates(){
    serial_print_coordinates();
    vision_print_coordinates();
}
