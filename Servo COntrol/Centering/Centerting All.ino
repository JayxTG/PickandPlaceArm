#include <Servo.h>

// Create servo objects for each joint of the robotic arm
Servo baseServo;    // Base rotation (Joint 1)
Servo shoulderServo; // Shoulder (Joint 2)
Servo elbowServo;    // Elbow (Joint 3)
Servo wristPitchServo;  // Wrist pitch (Joint 4)
Servo wristYawServo;    // Wrist yaw (Joint 5)
Servo gripperServo;     // Gripper (Joint 6)

void setup() {
  // Attach each servo to its respective pin
  baseServo.attach(9);        // Base servo connected to pin 9
  shoulderServo.attach(10);   // Shoulder servo connected to pin 10
  elbowServo.attach(11);      // Elbow servo connected to pin 11
  wristPitchServo.attach(12); // Wrist pitch servo connected to pin 12
  wristYawServo.attach(13);   // Wrist yaw servo connected to pin 13
  gripperServo.attach(6);     // Gripper servo connected to pin 6
}

void loop() {
  // Set each servo to the neutral position (1500 microseconds, 90 degrees)
  baseServo.writeMicroseconds(1500);        // Base rotation
  shoulderServo.writeMicroseconds(1500);    // Shoulder
  elbowServo.writeMicroseconds(1500);       // Elbow
  wristPitchServo.writeMicroseconds(1500);  // Wrist pitch
  wristYawServo.writeMicroseconds(1500);    // Wrist yaw
  gripperServo.writeMicroseconds(1500);     // Gripper

  delay(500);  // Wait for 500 milliseconds before repeating
}
