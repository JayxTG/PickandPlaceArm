#include "src/AsyncServo.h"

// Define 6 AsyncServo objects
AsyncServo asyncServo1;
AsyncServo asyncServo2;
AsyncServo asyncServo3;
AsyncServo asyncServo4;
AsyncServo asyncServo5;
AsyncServo asyncServo6;

// Define button pins
const int buttonA0 = A0;
const int buttonA1 = A1;
const int buttonA2 = A2;

// Define position states
enum PositionState
{
    PositionA,
    PositionA2,//Red Position
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

PositionState currentState = PositionA;

// Track movement completion
unsigned long movementStartTime = 0;
unsigned long movementDuration = 2000; // Duration in milliseconds

// Function to map angles (-90 to 90) to pulse widths (500 to 2500)
int mapAngleToPulseWidth(float angle) {
    return (int)((angle + 90) * (2500 - 500) / 180 + 500);
}

//Positions
//Red
float positionA[] = {52.44, 40.85, -60.50, 33.6, 0.0};
float positionB[] = {52.44, 40.85, -83.50, 38.6, 0.0};
float positionC[] = {-52.44, 40.85, -60.50, 33.65, 0.0};
float positionD[] = {-52.44, 40.85, -83.50, 38.65, 0.0};

//Green
float positionE[] = {45.60, 23.22, -65.54, 33.32, 0.0, 0.0};
float positionF[] = {45.60, 23.22, -85.54, 38.32, 0.0, 0.0};
float positionG[] = {-45.60, 23.22, -65.54, 33.32, 0.0, 0.0};
float positionH[] = {-45.60, 23.22, -85.54, 38.32, 0.0, 0.0};

//Blue
float positionI[] = {30.00, 25.00, -65.00, 20.00, 0.0, 0.0};
float positionJ[] = {30.00, 25.00, -85.00, 25.00, 0.0, 0.0};
float positionK[] = {-30.00, 25.00, -65.00, 20.00, 0.0, 0.0};
float positionL[] = {-30.00, 25.00, -85.00, 25.00, 0.0, 0.0};



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

    // Configure button pins as input with internal pull-up
    pinMode(buttonA0, INPUT_PULLUP);
    pinMode(buttonA1, INPUT_PULLUP);
    pinMode(buttonA2, INPUT_PULLUP);

    // Set output range for each servo (optional: adjust as needed)
    asyncServo1.SetOutput(500, 1500, 2500);
    asyncServo2.SetOutput(500, 1500, 2500);
    asyncServo3.SetOutput(500, 1500, 2500);
    asyncServo4.SetOutput(500, 1500, 2500);
    asyncServo5.SetOutput(500, 1500, 2500);

    delay(2000);

    while(true){
      
    // Check button presses
    if (digitalRead(buttonA0) == LOW) // Button A0 pressed
    {
        moveToPosition(positionA);
        currentState = PositionA;
        movementStartTime = millis(); // Reset movement timer
        Serial.println("Button A0 pressed: Starting Red positions.");
        break;
    }
    else if (digitalRead(buttonA1) == LOW) // Button A1 pressed
    {
        moveToPosition(positionE);
        currentState = PositionE;
        movementStartTime = millis(); // Reset movement timer
        Serial.println("Button A1 pressed: Starting Green positions.");
        break;
    }
    else if (digitalRead(buttonA2) == LOW) // Button A2 pressed
    {
        moveToPosition(positionI);
        currentState = PositionI;
        movementStartTime = millis(); // Reset movement timer
        Serial.println("Button A2 pressed: Starting Blue positions.");
        break;
    }

    }

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
    // Check if movement duration has elapsed
    if (millis() - movementStartTime > movementDuration)
    {
        switch (currentState)
        {
        // Red positions
        case PositionA:
            moveToPosition(positionB); // Transition to Position B
            currentState = PositionB;
            movementStartTime = millis();
            break;
        case PositionB:
            moveGripperTo2200(); // Move gripper to 2200
            currentState = GripperB;
            break;
        case GripperB:
            moveToPosition(positionA); // Return to Position C
            currentState = PositionA2;
            movementStartTime = millis();
            break;
        case PositionA2:
            moveToPosition(positionC); // Transition to Position B
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
            currentState = GripperA;
            break;
        case GripperA:
            moveToPosition(positionC); // Return to Position C2
            currentState = PositionC2;
            movementStartTime = millis();
            break;
        case PositionC2:
            moveToCenter(); // Go to Center
            movementStartTime = millis();
            break;

        // Green positions
        case PositionE:
            moveToPosition(positionF);
            currentState = PositionF;
            movementStartTime = millis();
            break;
        case PositionF:
            moveGripperTo2200();
            currentState = GripperF;
            break;
        case GripperF:
            moveToPosition(positionE);
            currentState = PositionE2;
            movementStartTime = millis();
            break;
        case PositionE2:
            moveToPosition(positionG);
            currentState = PositionG;
            movementStartTime = millis();
            break;
        case PositionG:
            moveToPosition(positionH);
            currentState = PositionH;
            movementStartTime = millis();
            break;
        case PositionH:
            moveGripperTo1500();
            currentState = GripperH;
            break;
        case GripperH:
            moveToPosition(positionG);
            currentState = PositionI; // Start Blue positions
            movementStartTime = millis();
            break;

        // Blue positions
        case PositionI:
            moveToPosition(positionJ);
            currentState = PositionJ;
            movementStartTime = millis();
            break;
        case PositionJ:
            moveGripperTo2200();
            currentState = GripperJ;
            break;
        case GripperJ:
            moveToPosition(positionI);
            currentState = PositionI2;
            movementStartTime = millis();
            break;
        case PositionI2:
            moveToPosition(positionK);
            currentState = PositionK;
            movementStartTime = millis();
            break;
        case PositionK:
            moveToPosition(positionL);
            currentState = PositionL;
            movementStartTime = millis();
            break;
        case PositionL:
            moveGripperTo1500();
            currentState = GripperL;
            break;
        case GripperL:
            moveToPosition(positionK);
            currentState = Center; // Return to center
            movementStartTime = millis();
            break;

        // Final center state
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
