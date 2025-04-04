#ifndef WIFI_COMMUNICATION_H
#define WIFI_COMMUNICATION_H

#define XY 1
#define X 2
#define Y 3
#define THETA 4
#define ALL 5

void get_coordinates(float r, float theta, int pick);

void serial_print_coordinates();
void vision_print_coordinates();
void print_coordinates();

#endif WIFI_COMMUNICATION_H
