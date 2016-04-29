/*
#
# TecnoCONGA_Ultrasonic.cpp
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

#include "TecnoCONGA_Ultrasonic.h"

TC_Ultrasonic::TC_Ultrasonic(byte triggerPin, byte echoPin) {
	this->triggerPin = triggerPin;
	this->echoPin    = echoPin;
	this->soundSpeed = 26;
	this->timeout    = 5000;
	
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin,    INPUT);
}

TC_Ultrasonic::TC_Ultrasonic(byte triggerPin, byte echoPin, unsigned long timeout) {
	this->triggerPin = triggerPin;
	this->echoPin    = echoPin;
	this->soundSpeed = 26;
	this->timeout    = timeout;
	
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin,    INPUT);
}

void TC_Ultrasonic::setTimeout(unsigned long timeout) {
	if(timeout == 0) {
		this->timeout = 5000;
	}
	
	this->timeout = timeout;
}

unsigned long TC_Ultrasonic::getTimeout() {
	return this->timeout;
}

void TC_Ultrasonic::setSoundSpeed(float speed) {
	if(speed == 0.0) {
		this->soundSpeed = 26;
		return;
	}
	
	this->soundSpeed = speed;
}

float TC_Ultrasonic::getSoundSpeed() {
	return this->soundSpeed;
}

float TC_Ultrasonic::calculateSoundSpeed(float distance) {
	// Send a 10us pulse to the TRIG pin
	this->triggerPulse();
	
	// Calculate the elapsed time for the sound to go and return
	pinMode(this->echoPin, INPUT);
	int pulseDuration = (int)pulseIn(this->echoPin, HIGH, this->timeout);
	
	// If the pulse duration is 0, timeout happened
	if(pulseDuration == 0) {
		return 0;
	}
	
	// Finally, calculate the sound hit speed (us/cm)
	float speed = ((float)pulseDuration) / 2.0 / distance;
	
	// Return the result
	return speed;
}

float TC_Ultrasonic::getHitDistance() {
	int hitTime = this->getHitTime();
	
	if(hitTime == 0) {
		return 0;
	}
	
	float distance = hitTime / this->soundSpeed;
	
	return distance;
}

int TC_Ultrasonic::getHitTime() {
	// Send a 10us pulse to the TRIG pin
	this->triggerPulse();
	
	// Calculate the elapsed time for the sound to go and return
	pinMode(this->echoPin, INPUT);
	int pulseDuration = (int)pulseIn(this->echoPin, HIGH, this->timeout);
	
	// If the pulse duration is 0, timeout happened
	if(pulseDuration == 0) {
		return 0;
	}
	
	// Divide by two, because we are only counting the time the pulse took to go
	int timeToHit = pulseDuration / 2;
	
	// Return the result
	return timeToHit;
}
void TC_Ultrasonic::triggerPulse() {
	// Make sure the pin is in output mode
	pinMode(this->triggerPin, OUTPUT);
	
	// Make sure the trigger pin is low
	digitalWrite(this->triggerPin, LOW);
	delayMicroseconds(2);
	
	// Send a 10us pulse (as described in the HC-SR04 datasheet)
	digitalWrite(this->triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->triggerPin, LOW);
}
