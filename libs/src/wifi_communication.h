/*
 * Written by Thomas Kimberlin
 */

#ifndef WIFI_COMMUNICATION_H
#define WIFI_COMMUNICATION_H

#define XY 1
#define X 2
#define Y 3
#define THETA 4
#define ALL 5

#define TRUE 1
#define FALSE 0

void get_coordinates(int pick);
int visibility_check(int pick);

void serial_print_coordinates();
void vision_print_coordinates();
void print_coordinates();

int compare_angles(coordinate origin, coordinate *compare, float tolerance, int *origin_t_greater);

#endif WIFI_COMMUNICATION_H
