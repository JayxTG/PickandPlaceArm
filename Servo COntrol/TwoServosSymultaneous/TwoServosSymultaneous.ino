/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "src/AsyncServo.h"

AsyncServo asyncServo09;
AsyncServo asyncServo10;

void setup()
{
	Serial.begin(115200);
	Serial.println("Restart");
	
	asyncServo09.Attach(3);
	

	asyncServo09.SetOutput(500, 1500, 2500);
  delay(500);

	step1();

}

void step1()
{
	asyncServo09.Move(1000, 4000, step2);
}

void step2()
{
	asyncServo09.Move(2000, 4000, step1);
}




void loop()
{
	delay(10);
	asyncServo09.Update();
	
}