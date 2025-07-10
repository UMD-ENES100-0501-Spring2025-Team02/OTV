/*
 * Written by Thomas Kimberlin
 */

#include "OTV_math.h"

/*
 * The vision system sends heading coordinates in the interval (-PI, PI]. The project code is written with respect to the interval [0, 2*PI) for simplicity
 * with the help of the following fucntion.
 */
void change_interval(float *theta){
    while (*theta < 0) *theta += 2 * PI;
    while (*theta >= 2 * PI) *theta -= 2 * PI;
}

/*
 * This function determines the angle between the x-axis and a coordinate p given the origin is shifted to the origin coordinate. This will also alter the theta
 * component of coordinate p.
 */
float calculate_angle(coordinate origin, coordinate *p) {
    float dx = p->x - origin.x;
    float dy = p->y - origin.y;
    
    // The function atan2() changes the angle given the signs of dy and dx to reflect the angle with respect to the x-axis within the interval [0, 2*PI)
    p->theta = atan2(dy, dx);
    change_interval(&p->theta);
    return p->theta;
}
