/*
#
# TecnoCONGA_Ultrasonic.h
#
# Copyright 2016 TecnoCONGA and the project contributors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/

#ifndef TecnoCONGA_Ultrasonic
#define TecnoCONGA_Ultrasonic

#include "Arduino.h"

class TC_Ultrasonic {
	public:
		TC_Ultrasonic(byte triggerPin, byte echoPin);
		TC_Ultrasonic(byte triggerPin, byte echoPin, unsigned long timeout);
		void setTimeout(unsigned long timeout);
		void setSoundPace(float pace);
		unsigned long getTimeout();                
		float getSoundPace();
		float calculateSoundPace(float distance);
		float getHitDistance();
		int getHitTime();
		
		
	private:
		byte triggerPin;
		byte echoPin;
		float soundPace;
		unsigned long timeout;
		
		void triggerPulse();
};

#endif
