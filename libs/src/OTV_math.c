#include "OTV_math.h"

// Interval is changed to be from [0, 2 * PI]
void change_interval(float *theta){
    while (*theta < 0) *theta += 2 * PI;
    while (*theta >= 2 * PI) *theta -= 2 * PI;
}


float calculate_angle(coordinate origin, coordinate *p) {
    float dx = p->x - origin.x;
    float dy = p->y - origin.y;
    p->theta = atan2(dy, dx); // angle in radians, [-pi, pi]
    change_interval(&p->theta);
    return p->theta;
}
