# ST_HW_HC_SR04
Advanced arduino library for HC-SR04 ultrasonic sensors

## Usage
Basic example:
```arduino
#include <ST_HW_HC_SR04.h>

ST_HW_HC_SR04 ultrasonicSensor(13, 12); // ST_HW_HC_SR04(TRIG, ECHO)

// Get the time the ultrasonic pulses took from the sensor to the blocking object
int hitTime = ultrasonicSensor.getHitTime();

// Calculate the approximate distance in centimeters (as seen in extras/HC-SR04.txt)
int distanceInCm = hitTIme / 58;
```

  The `getHitTime` function will return `0` if the ultrasonic sensor doesn't
receive back the packets it sent before the timeout value.

## Timeouts
  The default timeout value is `5000` microseconds, which sould be enough for approximately
*43 centimeters* ([5000  / 2 / 58] ~= 43.1).

  Although I didn't confirm, it is stated in [this datasheet](http://www.micropik.com/PDF/HCSR04.pdf)
([alternate link](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)) that max. range
of this sensor is 4 meters (400cm). As so, setting the timeout value to 46400 microseconds (46.4 ms)
should be enough for all cases where the object distance is less or equal to 4 meters.

The timeout-related methods of this library are:
```arduino
// Setters
ultrasonicSensor.setTimeout(unsigned long desiredTimeout);
ultrasonicSensor.setTimeoutToDefaultValue();

// Getters
unsigned long currentTimeout = ultrasonicSensor.getTimeout();
```

## Extra information
  Information about how the ultrasonic sensor works is present in the
`extras/HC-SR04.txt` file.
