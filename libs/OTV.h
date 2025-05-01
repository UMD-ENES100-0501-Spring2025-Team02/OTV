#ifndef OTV_H
#define OTV_H

// External Libraries

#include "ext_libs/ENES100ArduinoLibrary/Enes100.h"
#include "ext_libs/ENES100ArduinoLibrary/VisionSystemClient.cpp"
#include <Servo.h>
// Get the servo library on here

// Custom Libraries

#include "src/motor_controls.c"
#include "src/structs.h"
#include "src/OTV_math.c"
#include "src/wifi_communication.c"
#include "src/movement.c"
#include "src/mission_navigation.c"
#include "src/mission_objective.cpp"
#include "src/log_navigation.c"

#endif OTV_H
