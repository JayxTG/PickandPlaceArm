/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
****************************************************/

#include "src/AsyncServo.h"

// Define 6 AsyncServo objects
AsyncServo asyncServo1;
AsyncServo asyncServo2;
AsyncServo asyncServo3;
AsyncServo asyncServo4;
AsyncServo asyncServo5;
AsyncServo asyncServo6;

// Function to map floating-point angles to pulse widths
int mapAngleToPulseWidth(float angle) {
    return (int)((angle + 90) * (2500 - 500) / 180 + 500); // Linear mapping formula

}

// Array of input angles for the servos
// float servoAngles[] = {41.60, 40.79, -76.10, 39.30, 0.0}; 
//float servoAngles[] = {41.60, 30.79, -66.10, 35.30, 0.0}; 
//float servoAngles[] = {41.60, 45.75, -54.5, -10.2, 0.0}; 
// float servoAngles[] = {41.60, 17.38, -63.60, 37.3, 0.0}; 
 //float servoAngles[] = {41.60, 23.22, -65.54, 38.32, 0.0}; //working fine for positive
//  float servoAngles[] = {-48.51,-6.13,-24.11,26.25,0.0}; 
// float servoAngles[] = {-43.39,23.22,-65.54,38.32,0.0}; 
// float servoAngles[] = {-52.44,40.85,-83.5,38.65,0.0};  //Working Fine for neagtive
float servoAngles[] = {49.81,40.85,-83.50,38.6,0.0}; 

//when negative given reduce 5 negative values

void setup()
{
    Serial.begin(115200);
    Serial.println("Restart");

    // Attach servos to their respective pins
    asyncServo1.Attach(3);  // Servo 1 on pin 3
    asyncServo2.Attach(5);  // Servo 2 on pin 5
    asyncServo3.Attach(6);  // Servo 3 on pin 6
    asyncServo4.Attach(9);  // Servo 4 on pin 9
    asyncServo5.Attach(11); // Servo 5 on pin 11
    asyncServo6.Attach(10); // Servo 6 on pin 10

    // Set output range for each servo (optional: adjust as needed)
    asyncServo1.SetOutput(500, 1500, 2500);
    asyncServo2.SetOutput(500, 1500, 2500);
    asyncServo3.SetOutput(500, 1500, 2500);
    asyncServo4.SetOutput(500, 1500, 2500);
    asyncServo5.SetOutput(500, 1500, 2500);
    asyncServo6.SetOutput(500, 1500, 2500);

    delay(2000);

    // Move all servos using angles from the list
    moveServos(servoAngles);
}

// Function to move all servos based on input angles
void moveServos(float angles[]) {
    asyncServo1.Move(mapAngleToPulseWidth(angles[0]), 3000);
    asyncServo2.Move(mapAngleToPulseWidth(angles[1]), 3000);
    asyncServo3.Move(mapAngleToPulseWidth(angles[2]), 3000);
    asyncServo4.Move(mapAngleToPulseWidth(angles[3]), 3000);
    asyncServo5.Move(mapAngleToPulseWidth(angles[4]), 3000);
   
}

void loop()
{
    asyncServo1.Update();
    asyncServo2.Update();
    asyncServo3.Update();
    asyncServo4.Update();
    asyncServo5.Update();
    asyncServo6.Update();
}
