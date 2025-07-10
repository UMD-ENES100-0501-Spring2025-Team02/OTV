/*
 * Written by Ryan Tran
 */

#include "mission_objective.hpp"

void stage02(){
    if (!hasFlipped) {
        hasFlipped = true;
        flipSilo();
        
        is_it_magnetic();
        
        int DUTY = detectCycle();
        if (DUTY != 0) {
            Enes100.mission(CYCLE, DUTY);
        } else {
            Enes100.println("Failed Duty Cycle");
        }
    }
    
    // EDIT: The flipping servo was never reattached after being detatched in flipSilo() so this may not do anything other than add more delay
    FLIP.write(180);
    delay(2000);
    return;
}

/*
 * The strategy to pick up the pylon is to grab the claw and move forward for multiple "pulses", and for the final pulse, start flipping the pylon onto the OTV.
 * Once the pylon is flipped, the claw will open to ensure the pylon is fully secured on the OTV interface plate. Delays in this function are used to wait
 * for certain actions to complete and should be altered based on physical conditions.
 */
void flipSilo() {
    // Pulse one
    FLIP.attach(FLIP_SERVO_PIN);
    CLAW.write(CLOSE_CLAW);
    delay(1000);
    move(255, FORWARD, MIS);
    CLAW.write(CLOSE_CLAW_MORE);
    delay(1500);
    stop_drive();
    delay(1000);

    // Pulse two
    if (visibility_check(ALL)){
        if (otv.y < 1){
            move(255, FORWARD, MIS);
            CLAW.write(CLOSE_CLAW_MORE);
            delay(500);
        }
    }

    // Pulse three
    FLIP.write(0);
    move(255, FORWARD, MIS);
    delay(750);
    stop_drive();
    delay(2000);

    // Secures the pylon on interface plate
    FLIP.detach(); CLAW.write(OPEN_CLAW); delay(2200);
    CLAW.detach();
}

void is_it_magnetic() {
    bool magneticDetected = false;
    
    /*
     * This loop is believed to be the cause of a major bug where the OTV will reset to stage01() and repeat the main loop. We hypothesize that the loop overloads
     * the Arduino CPU causing it to reset, however this may not be the case and it could be some other physical or code issue that has not been observed by the team.
     * Although this is a major bug, usually the OTV does get past this bug at some point and is able to finish the objectives under 5 minutes.
     */
    for (int i = 0; i < 10; i++) {
        if (digitalRead(REED1) == LOW || digitalRead(REED2) == LOW || digitalRead(REED3) == LOW) {
            magneticDetected = true;
            // Loop exits early if magnets are detected
            break;
        }
        delay(100);
    }
  
    if (magneticDetected) {
        Enes100.mission(MAGNETISM, MAGNETIC);
        // EDIT: This boolean serves no purpose
        bool checked = false;
    } else {
        Enes100.mission(MAGNETISM, NOT_MAGNETIC);
    }
    
    delay(1000);
}

int detectCycle() {
    unsigned long highTime = pulseIn(DUTY_PIN, LOW, 1000000); // Max 1 sec
    unsigned long lowTime = pulseIn(DUTY_PIN, HIGH, 1000000);

    if (highTime == 0 || lowTime == 0) {
        return 0;
    }
    
    float dutyCycle = (float)lowTime / (highTime + lowTime) * 100.0;
    int level = round(dutyCycle / 10.0); // Map 10–100% to 1–10
    level = constrain(level, 1, 10);
    int percentage = level * 10;
    return percentage;
}
