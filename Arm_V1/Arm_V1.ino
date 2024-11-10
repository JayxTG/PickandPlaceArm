#include <Servo.h>
#include <math.h>

// Create servo objects
Servo servo_waist;
Servo servo_shoulder;
Servo servo_elbow;
Servo servo_wristpitch;
Servo servo_wristroll;
Servo servo_claw;

// Robot arm dimensions (in cm)
const float L1 = 10.0;  // Base to shoulder height
const float L2 = 12.0;  // Upper arm length
const float L3 = 12.0;  // Forearm length
const float L4 = 8.0;   // Wrist to end-effector length

// Time constants
const unsigned long timeinterval = 15;
unsigned long timepast = 0;

// Structure to store position and orientation
struct Pose {
    float x, y, z;     
    float roll, pitch, yaw;  
};

// Structure to store joint angles
struct JointAngles {
    float theta1;  // Waist
    float theta2;  // Shoulder
    float theta3;  // Elbow
    float theta4;  // Wrist pitch
    float theta5;  // Wrist roll
    float theta6;  // Claw
};

// Function to calculate inverse kinematics
JointAngles inverseKinematics(Pose target) {
    JointAngles angles;
    
    // Calculate waist angle (theta1)
    angles.theta1 = atan2(target.y, target.x);
    
    // Calculate wrist position
    float wrist_x = target.x - L4 * cos(target.pitch) * cos(angles.theta1);
    float wrist_y = target.y - L4 * cos(target.pitch) * sin(angles.theta1);
    float wrist_z = target.z - L4 * sin(target.pitch);
    
    // Calculate distance to wrist
    float r = sqrt(wrist_x*wrist_x + wrist_y*wrist_y);
    float s = wrist_z - L1;
    float D = sqrt(r*r + s*s);
    
    // Calculate shoulder and elbow angles using cosine law
    float cos_theta3 = (D*D - L2*L2 - L3*L3)/(2*L2*L3);
    angles.theta3 = acos(cos_theta3);
    
    float beta = atan2(s, r);
    float alpha = acos((L2*L2 + D*D - L3*L3)/(2*L2*D));
    angles.theta2 = beta + alpha;
    
    // Calculate wrist angles
    angles.theta4 = target.pitch - (angles.theta2 + angles.theta3);
    angles.theta5 = target.roll;
    
    // Convert angles to degrees
    angles.theta1 = degrees(angles.theta1);
    angles.theta2 = degrees(angles.theta2);
    angles.theta3 = degrees(angles.theta3);
    angles.theta4 = degrees(angles.theta4);
    angles.theta5 = degrees(angles.theta5);
    
    return angles;
}

// Function to move servos to target angles
void moveToAngles(JointAngles angles) {
    // Map 
    int servo_waist_val = constrain(map(angles.theta1, -90, 90, 0, 180), 0, 180);
    int servo_shoulder_val = constrain(map(angles.theta2, -90, 90, 0, 180), 0, 180);
    int servo_elbow_val = constrain(map(angles.theta3, -90, 90, 0, 180), 0, 180);
    int servo_wristpitch_val = constrain(map(angles.theta4, -90, 90, 0, 180), 0, 180);
    int servo_wristroll_val = constrain(map(angles.theta5, -90, 90, 0, 180), 0, 180);
    
    servo_waist.write(servo_waist_val);
    servo_shoulder.write(servo_shoulder_val);
    servo_elbow.write(servo_elbow_val);
    servo_wristpitch.write(servo_wristpitch_val);
    servo_wristroll.write(servo_wristroll_val);
}

// Function to perform pick and place operation
void pickAndPlace(Pose pickup_pose, Pose place_pose) {
    
    Pose approach_pose = pickup_pose;
    approach_pose.z += 5.0;  
    
    JointAngles angles = inverseKinematics(approach_pose);
    moveToAngles(angles);
    delay(1000);
    
    Serial.println("Initial Configuration:");
    Serial.print("Joint Angles (degrees): ");
    Serial.print(angles.theta1); Serial.print(", ");
    Serial.print(angles.theta2); Serial.print(", ");
    Serial.print(angles.theta3); Serial.print(", ");
    Serial.print(angles.theta4); Serial.print(", ");
    Serial.println(angles.theta5);
    
    angles = inverseKinematics(pickup_pose);
    moveToAngles(angles);
    delay(500);
    
    servo_claw.write(180); 
    delay(500);
   
    angles = inverseKinematics(approach_pose);
    moveToAngles(angles);
    delay(500);
    
    Pose place_approach = place_pose;
    place_approach.z += 5.0;
    angles = inverseKinematics(place_approach);
    moveToAngles(angles);
    delay(1000);
    
    angles = inverseKinematics(place_pose);
    moveToAngles(angles);
    delay(500);
    
    Serial.println("Final Configuration:");
    Serial.print("Joint Angles (degrees): ");
    Serial.print(angles.theta1); Serial.print(", ");
    Serial.print(angles.theta2); Serial.print(", ");
    Serial.print(angles.theta3); Serial.print(", ");
    Serial.print(angles.theta4); Serial.print(", ");
    Serial.println(angles.theta5);
  
    servo_claw.write(0);  
    delay(500);

    angles = inverseKinematics(place_approach);
    moveToAngles(angles);
}

void setup() {
    // Attach servos to pins with updated pin assignments
    servo_waist.attach(22);      // Updated from pin 8
    servo_shoulder.attach(23);    // Updated from pin 7
    servo_elbow.attach(24);      // Updated from pin 5
    servo_wristpitch.attach(25);  // Updated from pin 4
    servo_wristroll.attach(26);   // Updated from pin 3
    servo_claw.attach(27);       // Updated from pin 2
    
    Serial.begin(9600);
}

void loop() {
    
    Pose pickup_pose = {20.0, 15.0, 0.0, 0.0, -90.0, 0.0};  // x, y, z, roll, pitch, yaw
    Pose place_pose = {25.0, -15.0, 0.0, 0.0, -90.0, 0.0};
    
    pickAndPlace(pickup_pose, place_pose);
    
    
    delay(5000);
}