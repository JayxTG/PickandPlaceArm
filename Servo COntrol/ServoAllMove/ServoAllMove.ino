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
  int pos; // Variable to store positions

  // Sweep all servos except gripper (180 degrees)
  for (pos = 0; pos <= 180; pos += 1) {
    baseServo.writeMicroseconds(angleToMicroseconds(pos));
    shoulderServo.writeMicroseconds(angleToMicroseconds(pos));
    elbowServo.writeMicroseconds(angleToMicroseconds(pos));
    wristPitchServo.writeMicroseconds(angleToMicroseconds(pos));
    wristRollServo.writeMicroseconds(angleToMicroseconds(pos));
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    baseServo.writeMicroseconds(angleToMicroseconds(pos));
    shoulderServo.writeMicroseconds(angleToMicroseconds(pos));
    elbowServo.writeMicroseconds(angleToMicroseconds(pos));
    wristPitchServo.writeMicroseconds(angleToMicroseconds(pos));
    wristRollServo.writeMicroseconds(angleToMicroseconds(pos));
    delay(15);
  }

  // Gripper sweep (90 degrees)
  for (pos = 0; pos <= 90; pos += 1) {
    gripperServo.writeMicroseconds(angleToMicroseconds(pos));
    delay(15);
  }
  for (pos = 90; pos >= 0; pos -= 1) {
    gripperServo.writeMicroseconds(angleToMicroseconds(pos));
    delay(15);
  }
}
