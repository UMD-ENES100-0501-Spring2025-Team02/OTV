#include <math.h>

// Interval is changed to be from [0, 2 * PI]
void change_interval(coordinate *coordinate, int interval){
    if (interval == STD_INTV){
        if (coordinate->theta < 0){
            coordinate->theta += 2 * PI;
        }
    } else {
        if (coordinate->theta > PI){
            coordinate->theta -= 2 * PI;
        }
    }
}

/*
 * This function creates a virtual reference point of the OTV based on the Aruco
 * readings. Physically, you must determine the raduis from the Aruco marker and
 * the angle from the point to the positive x-axis.
 */
void virtual_reference(coordinate *coordinate, float r, float theta){
    coordinate->theta = theta;
    coordinate->x = coordinate->x + r * (float)cos(theta);
    coordinate->y = coordinate->y + r * (float)sin(theta);
}
