// PIN ASSIGNMENTS

#define IN1 13
#define IN2 12
#define ENA 11

#define IN3 10
#define IN4 9
#define ENB 8

#define MIS 1
#define NAV 2

#define FORWARD 1
#define BACKWARD 2
#define RIGHT 3
#define LEFT 4

#define PWM 50


void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);



}

void loop() {
    move(PWM, FORWARD, MIS);
    Serial.println("Forward MIS");
    delay(5000);
    move(PWM, BACKWARD, MIS);
    Serial.println("Backward MIS");
    delay(5000);
    turn(PWM, RIGHT, MIS);
    Serial.println("Right MIS");
    delay(5000);
    turn(PWM, LEFT, MIS);
    Serial.println("Left MIS");
    delay(5000);

    stop_drive();
    Serial.println("STOP");
    delay(10000);

    move(PWM, FORWARD, NAV);
    Serial.println("Forward NAV");
    delay(5000);
    move(PWM, BACKWARD, NAV);
    Serial.println("Backward NAV");
    delay(5000);
    turn(PWM, RIGHT, NAV);
    Serial.println("Right NAV");
    delay(5000);
    turn(PWM, LEFT, NAV);
    Serial.println("Left NAV");
    delay(10000);

    stop_drive():
    Serial.println("STOP");
    delay(5000);

}

void move(int pwm, int dir, int face){
    if (face == MIS && dir == FORWARD || face == NAV && dir == BACKWARDS) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, pwm);
        analogWrite(ENB, pwm);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, pwm);
        analogWrite(ENB, pwm);
    }
}

void turn(int pwm, int dir, int face){
    if (face == MIS && dir == RIGHT || face == NAV && dir == LEFT){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, pwm);
        analogWrite(ENB, pwm);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, pwm);
        analogWrite(ENB, pwm);
    }
}

void stop_drive(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
}