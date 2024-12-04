#include "src/AsyncServo.h"

// Define 6 AsyncServo objects
AsyncServo asyncServo1;
AsyncServo asyncServo2;
AsyncServo asyncServo3;
AsyncServo asyncServo4;
AsyncServo asyncServo5;
AsyncServo asyncServo6;

// Define position states
enum PositionState
{
    PositionA,
    PositionA2,
    PositionB,
    PositionC,
    PositionC2,
    PositionD,
    GripperA,
    GripperB,
    Center,
    Idle
};
PositionState currentState = PositionA;

// Track movement completion
unsigned long movementStartTime = 0;
unsigned long movementDuration = 2000; // Duration in milliseconds

// Function to map angles (-90 to 90) to pulse widths (500 to 2500)
int mapAngleToPulseWidth(float angle) {
    return (int)((angle + 90) * (2500 - 500) / 180 + 500);
}

// Define positions using angle arrays (6 angles for each position)
float positionA[] = {52.44, 40.85, -60.50, 33.6, 0.0};
float positionB[] = {52.44, 40.85, -83.50, 38.6, 0.0};
float positionC[] = {-52.44, 40.85, -60.50, 33.65, 0.0};
float positionD[] = {-52.44, 40.85, -83.50, 38.65, 0.0};

// Preprocess positions: Adjust the 0th element if positive
void preprocessPosition(float position[]) {
    if (position[0] > 0) {
        position[0] -= 4;
    }
}

void preprocessAllPositions() {
    preprocessPosition(positionA);
    preprocessPosition(positionB);
    preprocessPosition(positionC);
    preprocessPosition(positionD);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Restart");

    // Preprocess all positions
    preprocessAllPositions();

    // Attach servos to their respective pins
    asyncServo1.Attach(3);
    asyncServo2.Attach(5);
    asyncServo3.Attach(6);
    asyncServo4.Attach(9);
    asyncServo5.Attach(11);
    asyncServo6.Attach(10);

    // Set output range for each servo (optional: adjust as needed)
    asyncServo1.SetOutput(500, 1500, 2500);
    asyncServo2.SetOutput(500, 1500, 2500);
    asyncServo3.SetOutput(500, 1500, 2500);
    asyncServo4.SetOutput(500, 1500, 2500);
    asyncServo5.SetOutput(500, 1500, 2500);

    delay(2000);

    // Start by moving to Position A
    moveToPosition(positionA);
    currentState = PositionA;
    movementStartTime = millis();
}

// Function to move servos based on angles and direct PWM for Servo 6
void moveToPosition(float angles[])
{
    asyncServo1.Move(mapAngleToPulseWidth(angles[0]), 2000);
    asyncServo2.Move(mapAngleToPulseWidth(angles[1]), 2000);
    asyncServo3.Move(mapAngleToPulseWidth(angles[2]), 2000);
    asyncServo4.Move(mapAngleToPulseWidth(angles[3]), 2000);
    asyncServo5.Move(mapAngleToPulseWidth(angles[4]), 2000);
}

void moveGripperTo1500()
{
    asyncServo6.Move(1500, 1000); // Move gripper to 1500
    currentState = GripperA;
    movementStartTime = millis();
}

void moveGripperTo2200()
{
    asyncServo6.Move(2200, 1000); // Move gripper to 2200
    currentState = GripperB; 
    movementStartTime = millis();
}

void moveToCenter()
{
    asyncServo1.Move(1500, 2000);
    asyncServo2.Move(1500, 2000);
    asyncServo3.Move(1500, 2000);
    asyncServo4.Move(1500, 2000);
    asyncServo5.Move(1500, 2000);
    currentState = Center;
}

void loop()
{
    // Update servo movements
    asyncServo1.Update();
    asyncServo2.Update();
    asyncServo3.Update();
    asyncServo4.Update();
    asyncServo5.Update();
    asyncServo6.Update();

    // Check if movement duration has elapsed
    if (millis() - movementStartTime > movementDuration)
    {
        switch (currentState)
        {
        case PositionA:
            moveToPosition(positionB); // Transition to Position B
            currentState = PositionB;
            movementStartTime = millis();
            break;
        case PositionB:
            moveGripperTo2200(); // Move gripper to 2200
            break;
        case GripperB:
            moveToPosition(positionA); // Return to Position A
            currentState = PositionA2;
            movementStartTime = millis();
            break;
        case PositionA2:
            moveToPosition(positionC); // Transition to Position C
            currentState = PositionC;
            movementStartTime = millis();
            break;
        case PositionC:
            moveToPosition(positionD); // Transition to Position D
            currentState = PositionD;
            movementStartTime = millis();
            break;
        case PositionD:
            moveGripperTo1500(); // Move gripper to 1500
            break;
        case GripperA:
            moveToPosition(positionC); // Return to Position C
            currentState = PositionC2;
            movementStartTime = millis();
            break;
        case PositionC2:
            moveToCenter(); // Go to Center
            movementStartTime = millis();
            break;
        case Center:
            currentState = Idle; // Task complete
            Serial.println("Task Complete. All Movements Done.");
            break;
        case Idle:
            // Do nothing, task is complete
            break;
        }
    }
}
