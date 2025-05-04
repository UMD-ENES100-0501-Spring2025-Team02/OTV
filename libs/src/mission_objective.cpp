#include "mission_objective.hpp"

void stage02(){ // run into silo as claw gripping, the second a duty cycle can be detected, detact the claw and flip motor
  if (!hasFlipped) {
    hasFlipped = true;
    flipSilo(); //otv moves forward while gripping
    is_it_magnetic();
    int DUTY = detectCycle();
    if (DUTY != 0) {
      Enes100.mission(CYCLE, DUTY);

    }
    else {
      Enes100.println("Is the Electrode in Contact with Silo");
    }
  }
  reverseSilo();
}

void flipSilo() {
  //pulse one
    FLIP.attach(FLIP_SERVO_PIN);
    CLAW.write(110); // close claw
    delay(1000);  // without delay it will run forward as the claw closes, with delay, it will close wait 0.5 seconds then start moving
    move(255, FORWARD, MIS);
    CLAW.write(115); // squeezing the living fuck out the silo
    delay(1500); // move forward for 0.5 seconds
    stop_drive();
    delay(1000);

  //pulse two
    if (visibility_check(ALL)){
        if (otv.y < 1){
            move(255, FORWARD, MIS);
            CLAW.write(110);
            delay(500);
        }
    }

  //pulse three
    FLIP.write(0);
    move(255, FORWARD, MIS);
    delay(750);
    stop_drive();
    Enes100.print("Waiting to open");
    delay(1200);

  //the big movement
    FLIP.detach(); CLAW.write(0); delay(2200); // rotate the silo add a bit of extra grip
    CLAW.detach();
}

void reverseSilo() {
  if (digitalRead(LEFT_LIMIT) == LOW){
    CLAW.attach(12);
    FLIP.attach(13);
    FLIP.write(180); // reverse the flip direction
    CLAW.write(0);   // open claw
    FLIP.detach(); CLAW.detach(); // save power
    hasFlipped = false;
  }
}

void is_it_magnetic() {
  bool magneticDetected = false;
  for (int i = 0; i < 1000; i++) {
    if (digitalRead(REED1) == LOW || digitalRead(REED2) == LOW || digitalRead(REED3) == LOW) {
      magneticDetected = true;
      break;  // Exit early if magnet is detected
    }
    delay(50);  // chatgpt recommended to not "overload CPU"
  }
  if (magneticDetected) {
    Enes100.mission(MAGNETISM, MAGNETIC);
    bool checked = false;
  }
  else {
    Enes100.mission(MAGNETISM, NOT_MAGNETIC);
  }
}

int detectCycle() {
  unsigned long highTime = pulseIn(DUTY_PIN, LOW, 1000000); // Max 1 sec
  unsigned long lowTime = pulseIn(DUTY_PIN, HIGH, 1000000);

  if (highTime == 0 || lowTime == 0) {
    Enes100.println("Is the Silo in contact?");
    return 0;
  }
    float dutyCycle = (float)lowTime / (highTime + lowTime) * 100.0;
    int level = round(dutyCycle / 10.0); // Map 10–100% to 1–10
    level = constrain(level, 1, 10);
    int percentage = level * 10;
    return percentage;
}
