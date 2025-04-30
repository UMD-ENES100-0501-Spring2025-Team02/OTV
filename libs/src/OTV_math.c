#include "OTV_math.h"

// Interval is changed to be from [0, 2 * PI]
void change_interval(float *theta){
    while (*theta < 0) *theta += 2 * PI;
    while (*theta >= 2 * PI) *theta -= 2 * PI;
}

/*
 * This function creates a virtual reference point of the OTV based on the Aruco
 * readings. Physically, you must determine the raduis from the Aruco marker and
 * the angle from the point to the positive x-axis.
 */
void virtual_reference(coordinate *coordinate, float r, float theta){
    float relative_theta = coordinate->theta + theta;
    change_interval(&relative_theta);
    coordinate->x = coordinate->x + r * (float)cos(relative_theta);
    coordinate->y = coordinate->y + r * (float)sin(relative_theta);
}

float angle_with_x_axis(coordinate origin, coordinate *p) {
    float dx = p->x - origin.x;
    float dy = p->y - origin.y;
    return p->theta = atan2(dy, dx); // angle in radians, [-pi, pi]
}
