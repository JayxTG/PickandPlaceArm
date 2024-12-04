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

}

void loop() {
  // Set each servo to the neutral position (1500 microseconds, 90 degrees)
  baseServo.writeMicroseconds(1500);        // Base rotation


  delay(500);  // Wait for 500 milliseconds before repeating
}
