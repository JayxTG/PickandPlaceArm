#include "src/AsyncServo.h"

// Define 6 AsyncServo objects
AsyncServo asyncServo1, asyncServo2, asyncServo3, asyncServo4, asyncServo5, asyncServo6;

// Define button pins
const int buttonA0 = A0;
const int buttonA1 = A1;
const int buttonA2 = A2;

// Angular velocity (degrees/second)
const float omega = 30; // Example angular velocity

// Define position states
enum PositionState
{
    PositionA,
    PositionA2, // Red Position
    PositionB,
    PositionC,
    PositionC2,
    PositionD,
    PositionE,
    PositionE2, // Green positions
    PositionF,
    PositionG,
    PositionG2,
    PositionH,
    PositionI,
    PositionI2, // Blue positions
    PositionJ,
    PositionK,
    PositionK2,
    PositionL,
    Center,
    Idle,
    GripperA,
    GripperB,
    GripperF,
    GripperH,
    GripperJ,
    GripperL
};

PositionState currentState;

// Red {52.44, 40.85, -83.50, 38.6, 0.0};
float positionA[] = {53.81, 74.31, -73.68, -4.62, 0.0};
float positionB[] = {53.81, 40.85, -83.50, 38.65, 0.0}; //(20,15)
float positionC[] = {-44.3, 76.43, -74.79, -5.63, 0.0};
float positionD[] = {-44.30, 42.57, -84.93, 38.35, 0.0};// (17.5,17.5)

// Green
float positionE[] = {37.5575, 74.31, -73.68, -4.62, 0.0};
float positionF[] = {37.5575, 40.85, -83.50, 38.65, 0.0};
float positionG[] = {-37.27, 49.21, -57.25, 4.04, 0.0};
float positionH[] = {-37.27, 22.23, -64.35, 38.12, 0.1};

// Blue
float positionI[] = {22.439, 59.623, -64.885, 1.262, 0.0};
float positionJ[] = {22.439, 29.750, -72.911, 39.162, 0.0};
float positionK[] = {-31.943, 26.058, -35.473, 5.416, 0.0};
float positionL[] = {-31.943, 5.162, -41.341, 32.179, 0.0};

//center
float center[] = {0, 0, 0, 0, 0, 0}; 

// Time tracking
unsigned long movementStartTime = 0;
unsigned long movementDuration = 0; // Duration in milliseconds

// Function to map angles (-90 to 90) to pulse widths (500 to 2500)
int mapAngleToPulseWidth(float angle)
{
    return (int)((angle + 90) * (2500 - 500) / 180 + 500);
}

// Calculate the maximum turning angle between two positions
float getMaxTurningAngle(float position1[], float position2[])
{
    float maxAngle = 0;
    for (int i = 0; i < 5; i++) // Assuming 5 servos
    {
        float angleChange = abs(position2[i] - position1[i]);
        if (angleChange > maxAngle)
        {
            maxAngle = angleChange;
        }
    }
    return maxAngle;
}

// Calculate movement time dynamically
float calculateMovementTime(float position1[], float position2[])
{
    float maxAngle = getMaxTurningAngle(position1, position2);
    return (maxAngle / omega) * 1000; // Time in milliseconds
}

// Preprocess positions: Adjust the 0th element if positive
void preprocessPosition(float position[])
{
    if (position[0] > 0)
    {
        position[0] = position[0]-3;
        Serial.print(position[0]);
    } 
}

void preprocessAllPositions()
{
    preprocessPosition(positionA);
    preprocessPosition(positionB);
    preprocessPosition(positionC);
    preprocessPosition(positionD);
    preprocessPosition(positionE);
    preprocessPosition(positionF);
    preprocessPosition(positionG);
    preprocessPosition(positionH);
    preprocessPosition(positionI);
    preprocessPosition(positionJ);
    preprocessPosition(positionK);
    preprocessPosition(positionL);
}

// Function to move servos based on angles and duration
void moveToPosition(float angles[], float duration)
{
    asyncServo1.Move(mapAngleToPulseWidth(angles[0]), duration);
    asyncServo2.Move(mapAngleToPulseWidth(angles[1]), duration);
    asyncServo3.Move(mapAngleToPulseWidth(angles[2]), duration);
    asyncServo4.Move(mapAngleToPulseWidth(angles[3]), duration);
    asyncServo5.Move(mapAngleToPulseWidth(angles[4]), duration);
    movementDuration = duration; // Set movement duration
}

void moveGripperTo1500()
{
    asyncServo6.Move(1500, 1000); // Move gripper to 1500
    currentState = GripperA;
    movementStartTime = millis();
}

void moveGripperTo2200()
{
    asyncServo6.Move(1800, 1000); // Move gripper to 2200
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

    // Configure button pins as input with internal pull-up
    pinMode(buttonA0, INPUT_PULLUP);
    pinMode(buttonA1, INPUT_PULLUP);
    pinMode(buttonA2, INPUT_PULLUP);

    delay(2000);

    while (true)
    {
        if (digitalRead(buttonA0) == LOW)
        {
            moveToPosition(positionA, calculateMovementTime(center, positionA));
            currentState = PositionA;
            movementStartTime = millis();
            break;
        }
        else if (digitalRead(buttonA1) == LOW)
        {
            moveToPosition(positionE, calculateMovementTime(center, positionE));
            currentState = PositionE;
            movementStartTime = millis();
            break;
        }
        else if (digitalRead(buttonA2) == LOW)
        {
            moveToPosition(positionI, calculateMovementTime(center, positionI));
            currentState = PositionI;
            movementStartTime = millis();
            break;
        }
    }
}

void loop()
{
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
            // Red positions
            case PositionA:
                moveToPosition(positionB, calculateMovementTime(positionA, positionB)); // Transition to Position B
                currentState = PositionB;
                movementStartTime = millis();
                break;

            case PositionB:
                moveGripperTo2200(); // Move gripper to 2200
                currentState = GripperB;
                break;

            case GripperB:
                moveToPosition(positionA, calculateMovementTime(positionB, positionA)); // Return to Position A2
                currentState = PositionA2;
                movementStartTime = millis();
                break;

            case PositionA2:
                moveToPosition(positionC, calculateMovementTime(positionA, positionC)); // Transition to Position C
                currentState = PositionC;
                movementStartTime = millis();
                break;

            case PositionC:
                moveToPosition(positionD, calculateMovementTime(positionC, positionD)); // Transition to Position D
                currentState = PositionD;
                movementStartTime = millis();
                break;

            case PositionD:
                moveGripperTo1500(); // Move gripper to 1500
                currentState = GripperA;
                break;

            case GripperA:
                moveToPosition(positionC, calculateMovementTime(positionD, positionC)); // Return to Position C2
                currentState = PositionC2;
                movementStartTime = millis();
                break;

            case PositionC2:
                moveToCenter(); // Go to Center
                movementStartTime = millis();
                break;

            // Green positions
            case PositionE:
                moveToPosition(positionF, calculateMovementTime(positionE, positionF)); // Transition to Position F
                currentState = PositionF;
                movementStartTime = millis();
                break;

            case PositionF:
                moveGripperTo2200(); // Move gripper to 2200
                currentState = GripperH;
                break;

            case GripperH:
                moveToPosition(positionE, calculateMovementTime(positionF, positionE)); // Return to Position E2
                currentState = PositionE2;
                movementStartTime = millis();
                break;

            case PositionE2:
                moveToPosition(positionG, calculateMovementTime(positionE, positionG)); // Transition to Position G
                currentState = PositionG;
                movementStartTime = millis();
                break;

            case PositionG:
                moveToPosition(positionH, calculateMovementTime(positionG, positionH)); // Transition to Position H
                currentState = PositionH;
                movementStartTime = millis();
                break;

            case PositionH:
                moveGripperTo1500(); // Move gripper to 1500
                currentState = GripperF;
                break;

            case GripperF:
                moveToPosition(positionG, calculateMovementTime(positionH, positionG)); // Return to Position G2
                currentState = PositionG2;
                movementStartTime = millis();
                break;

            case PositionG2:
                moveToCenter(); // Go to Center
                movementStartTime = millis();
                break;

            // Blue positions
            case PositionI:
                moveToPosition(positionJ, calculateMovementTime(positionI, positionJ)); // Transition to Position J
                currentState = PositionJ;
                movementStartTime = millis();
                break;

            case PositionJ:
                moveGripperTo2200(); // Move gripper to 2200
                currentState = GripperL;
                break;          


            case GripperL:
                moveToPosition(positionI, calculateMovementTime(positionJ, positionI)); // Return to Position K2
                currentState = PositionI2;
                movementStartTime = millis();
                break;

            case PositionI2:
                moveToPosition(positionK, calculateMovementTime(positionI, positionK)); // Transition to Position K
                currentState = PositionK;
                movementStartTime = millis();
                break;

            case PositionK:
                moveToPosition(positionL, calculateMovementTime(positionK, positionL)); // Transition to Position J
                currentState = PositionL;
                movementStartTime = millis();
                break;

            case PositionL:
                moveGripperTo1500(); // Move gripper to 1500
                currentState = GripperJ;
                break;

            case GripperJ:
                moveToPosition(positionK, calculateMovementTime(positionK, positionL)); // Transition to Position J
                currentState = PositionK2;
                movementStartTime = millis();
                break;

            case PositionK2:
                moveToCenter(); // Go to Center
                movementStartTime = millis();
                break;

            case Center:
                  while (true)
                  {
                      if (digitalRead(buttonA0) == LOW)
                      {
                          moveToPosition(positionA, calculateMovementTime(center, positionA));
                          currentState = PositionA;
                          movementStartTime = millis();
                          break;
                      }
                      else if (digitalRead(buttonA1) == LOW)
                      {
                          moveToPosition(positionE, calculateMovementTime(center, positionE));
                          currentState = PositionE;
                          movementStartTime = millis();
                          break;
                      }
                      else if (digitalRead(buttonA2) == LOW)
                      {
                          moveToPosition(positionI, calculateMovementTime(center, positionI));
                          currentState = PositionI;
                          movementStartTime = millis();
                          break;
                      }
                      break;
                  }
        }
  }
}
