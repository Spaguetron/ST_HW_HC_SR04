/*
#
# ST_HW_HC_SR04.cpp
#
*/

/*
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ST_HW_HC_SR04.h"

ST_HW_HC_SR04::ST_HW_HC_SR04(byte triggerPin, byte echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin    = echoPin;
    this->timeout    = 5000;

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin,    INPUT);
}

ST_HW_HC_SR04::ST_HW_HC_SR04(byte triggerPin, byte echoPin, unsigned long timeout) {
    this->triggerPin = triggerPin;
    this->echoPin    = echoPin;
    this->timeout    = timeout;

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin,    INPUT);
}

void ST_HW_HC_SR04::setTimeout(unsigned long timeout) {
    this->timeout = timeout;
}

void ST_HW_HC_SR04::setTimeoutToDefaultValue() {
    this->timeout = 5000;
}

unsigned long ST_HW_HC_SR04::getTimeout() {
    return this->timeout;
}

int ST_HW_HC_SR04::getHitTime() {
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

void ST_HW_HC_SR04::triggerPulse() {
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
