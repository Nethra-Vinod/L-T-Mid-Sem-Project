#include <Arduino.h>
#include <Servo.h>

// ---------------- Pin Definitions ---------------- //
// Ultrasonic
#define TRIG_PIN 18
#define ECHO_PIN 19

// Servo
#define SERVO_PIN 23

// Drive Motors (via L298N)
#define ENA 25
#define IN1 26
#define IN2 27
#define IN3 32
#define IN4 33
#define ENB 12

// Blade Motor (via L298N extra channel)
#define BLADE_EN 13
#define BLADE_IN1 14
#define BLADE_IN2 15

// ---------------- Constants ---------------- //
const int distanceThreshold = 20; // cm
#define PWM_FREQ 5000
#define PWM_RES 8

// ---------------- Objects ---------------- //
Servo scannerServo;

// ---------------- Setup ---------------- //
void setup() {
  Serial.begin(115200);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(BLADE_IN1, OUTPUT);
  pinMode(BLADE_IN2, OUTPUT);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Servo
  scannerServo.attach(SERVO_PIN);

  // Setup PWM channels
  ledcSetup(0, PWM_FREQ, PWM_RES); // ENA
  ledcSetup(1, PWM_FREQ, PWM_RES); // ENB
  ledcSetup(2, PWM_FREQ, PWM_RES); // Blade

  ledcAttachPin(ENA, 0);
  ledcAttachPin(ENB, 1);
  ledcAttachPin(BLADE_EN, 2);

  stopMotors();
  stopBlade();
}

// ---------------- Loop ---------------- //
void loop() {
  int distance = measureDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < distanceThreshold) {
    startBlade();
    avoidObstacle();
  } else {
    moveForward();
    stopBlade();
  }
}

// ---------------- Functions ---------------- //
int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) return 999;

  int distance = duration * 0.034 / 2;
  return distance;
}

// ---- Blade Motor ----
void startBlade() {
  digitalWrite(BLADE_IN1, HIGH);
  digitalWrite(BLADE_IN2, LOW);
  ledcWrite(2, 255); // Full speed
}

void stopBlade() {
  digitalWrite(BLADE_IN1, LOW);
  digitalWrite(BLADE_IN2, LOW);
  ledcWrite(2, 0);
}

// ---- Drive Motors ----
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  ledcWrite(0, 200); // ENA
  ledcWrite(1, 200); // ENB
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  ledcWrite(0, 0);
  ledcWrite(1, 0);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  ledcWrite(0, 200);
  ledcWrite(1, 0);
}

void avoidObstacle() {
  stopMotors();
  delay(300);

  turnRight();
  delay(600);

  stopMotors();
  delay(200);
}
