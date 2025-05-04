#ifndef MISSION_OBJECTIVE_H
#define MISSION_OBJECTIVE_H

Servo CLAW;
Servo FLIP;

bool hasFlipped = false;

void stage02();
void flipSilo();
void reverseSilo();
void is_it_magnetic();
int detectCycle();

#endif MISSION_OBJECTIVE_H
