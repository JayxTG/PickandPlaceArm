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




void setup()
{
    Serial.begin(115200);
    Serial.println("Restart");
    


    // Attach servos to their respective pins
    asyncServo1.Attach(3);  // Servo 1 on pin 3
    asyncServo2.Attach(5);  // Servo 2 on pin 5
    asyncServo3.Attach(6);  // Servo 3 on pin 6
    asyncServo4.Attach(9);  // Servo 4 on pin 9
    asyncServo5.Attach(11); // Servo 5 on pin 10
    asyncServo6.Attach(10); // Servo 6 on pin 11

    // Set output range for each servo (optional: adjust as needed)
    asyncServo1.SetOutput(500, 1500, 2500);
    asyncServo2.SetOutput(500, 1500, 2500);
    asyncServo3.SetOutput(500, 1500, 2500);
    asyncServo4.SetOutput(500, 1500, 2500);
    asyncServo5.SetOutput(500, 1500, 2500);
    asyncServo6.SetOutput(500, 1500, 2500);



    delay(2000);
	  // asyncServo1.Move(1500, 4000);
    // asyncServo2.Move(1500, 4000);
     step1();
     step2();
     step3();
     step4();
     step5();
     step6();
}
void step1()
{
	asyncServo1.Move(2134, 3000);
}

void step2()
{
	asyncServo2.Move(1726, 3000);
}

void step3()
{
	asyncServo3.Move(1130, 3000);
}

void step4()
{
	asyncServo4.Move(1732, 3000);
}

void step5()
{
	asyncServo5.Move(1500, 3000);
}

void step6()
{
	asyncServo6.Move(2200, 3000);
}





void loop()
{
  // asyncServo1.write(2000);
    asyncServo1.Update();
    asyncServo2.Update();
    asyncServo3.Update();
    asyncServo4.Update();
    asyncServo5.Update();
    asyncServo6.Update();
}
