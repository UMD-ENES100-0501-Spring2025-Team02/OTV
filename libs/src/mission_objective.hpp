/*
 * Written by Ryan Tran
 */

#ifndef MISSION_OBJECTIVE_H
#define MISSION_OBJECTIVE_H

// These values should be determined based on the behavior of the claw given the macro descriptions
#define CLOSE_CLAW 0
#define CLOSE_CLAW_MORE -5
#define OPEN_CLAW 120

Servo CLAW;
Servo FLIP;

bool hasFlipped = false;

void stage02();
void flipSilo();
void reverseSilo();
void is_it_magnetic();
int detectCycle();

#endif MISSION_OBJECTIVE_H
