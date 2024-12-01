#include <Servo.h>

// Create servo objects for each joint
Servo baseServo;        // Base rotation
Servo shoulderServo;    // Shoulder movement
Servo elbowServo;       // Elbow movement
Servo wristPitchServo;  // Wrist pitch
Servo wristRollServo;   // Wrist roll
Servo gripperServo;     // Gripper

// Function to convert an angle (in degrees) to pulse width in microseconds
int angleToMicroseconds(int angle) {
  return map(angle, 0, 180, 500, 2500); // Convert angle 0-180 to pulse width 500-2500
}

// Function to move a servo from 0 to maxAngle and back to 0
void moveServo(Servo &servo, int maxAngle) {
  for (int pos = 0; pos <= maxAngle; pos += 1) {
    servo.writeMicroseconds(angleToMicroseconds(pos));
    delay(15); // Adjust delay for smoothness
  }
  for (int pos = maxAngle; pos >= 0; pos -= 1) {
    servo.writeMicroseconds(angleToMicroseconds(pos));
    delay(15); // Adjust delay for smoothness
  }
}

void setup() {
  // Attach servos to pins
  baseServo.attach(3);        // Base servo on pin 3
  shoulderServo.attach(5);    // Shoulder servo on pin 5
  elbowServo.attach(6);       // Elbow servo on pin 6
  wristPitchServo.attach(9);  // Wrist pitch servo on pin 9
  wristRollServo.attach(10);  // Wrist roll servo on pin 10
  gripperServo.attach(11);    // Gripper servo on pin 11
}

void loop() {
  // Sequential movement of each servo
  moveServo(baseServo, 180);        // Move base servo 0-180 and back
  moveServo(shoulderServo, 180);    // Move shoulder servo 0-180 and back
  moveServo(elbowServo, 180);       // Move elbow servo 0-180 and back
  moveServo(wristPitchServo, 180);  // Move wrist pitch servo 0-180 and back
  moveServo(wristRollServo, 180);   // Move wrist roll servo 0-180 and back
  moveServo(gripperServo, 90);      // Move gripper servo 0-90 and back
}
