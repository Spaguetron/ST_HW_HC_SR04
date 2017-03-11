/*
#
# GetHitTime.ino - ST_HW_HC_SR04 v2.0 library example
#
#   This code shows you how to get the elapsed time the ultrasonic pulses sent
# by the sensor take from the HC-SR04 location to a blocking object (i.e. wall)
#
# The result can be seen every ~1.5 seconds by using the Serial Monitor
#
*/

#include <ST_HW_HC_SR04.h>

// Change the pins if you wish.
ST_HW_HC_SR04 ultrasonicSensor(13, 12); // ST_HW_HC_SR04(TRIG, ECHO)

void setup() {
    Serial.begin(9600);
}

void loop() {
    int hitTime = ultrasonicSensor.getHitTime(); // In microseconds

    /*
    #
    # This means the sensor didn't receive back the packets before the timeout
    #
    #   That usually happens when the distance between the sensor and the block-
    # ing object is greater than 40 centimeters (15.75 inches).
    #
    #   Increasing the timeout from 5000 microseconds to 50000 microseconds
    # will increase the maximum distance to ~4m, at the cost of the code being
    # stuck for 50ms if no packet is received during this period (worst case
    # scenario).
    #
    #   More information (including calculations) is included in the
    # extras/HC-SR04.txt file. (Inside your libraries/ST_HW_HC_SR04 folder)
    #
    */
    if(hitTime == 0) {
        if(ultrasonicSensor.getHitTime() == 5000) { // This is the default value
            Serial.println("Timeout happened, retrying with a greater timeout");
            ultrasonicSensor.setTimeout(50000);

            return; // Restart the loop
        }

        Serial.println("Timeout happening even with 50ms timeout, check your "
                       "sensor!");
    }

    String message = "The hit time was " + String(hitTime) + " microseconds";
    Serial.println(message);

    delay(1500); // Delay 1500ms (1.5s)
}
