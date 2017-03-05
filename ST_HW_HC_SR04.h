/*
#
# ST_HW_HC_SR04.h
#
# (C)2016-2017 Flávio monteiro
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

#ifndef ST_HW_HC_SR04
#define ST_HW_HC_SR04

#include "Arduino.h"

class ST_HW_HC_SR04 {
    public:
        ST_HW_HC_SR04(byte triggerPin, byte echoPin);
        ST_HW_HC_SR04(byte triggerPin, byte echoPin, unsigned long timeout);
        void setTimeout(unsigned long timeout);
        void setTimeoutToDefaultValue();
        unsigned long getTimeout();
        int getHitTime();

    private:
        byte triggerPin;
        byte echoPin;
        unsigned long timeout;

        void triggerPulse();
};

#endif
