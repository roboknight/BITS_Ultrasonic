#include "Arduino.h"

#ifndef __RANGEFINDER_H__
#define __RANGEFINDER_H__

extern int debug_lvl;

// NOTE: The define here creates
//       a method for controling
//       debug output so we can
//       turn it off simply by
//       undefining the above
//       variable, "_DEBUG_"
#define rf_debugPrint(lvl,s,val) \
        if (debug_lvl >= lvl) { \
          Serial.print(s); \
          Serial.println((float)val); \
        }

class RangeFinder {
    public:
    RangeFinder(int triggerPin, int echoPin);
    RangeFinder(int triggerPin, int echoPin, int minRange, int maxRange);
    unsigned long pingRange(void);
    unsigned long pingRange(unsigned long to);
    float distanceInMillimeters(void);
    float filterRangeMillimeters(void);
    private:
    int _triggerPin;
    int _echoPin;
    int _minRange = -1;
    int _maxRange = -1;
    unsigned long _pingTime;
};

#endif // __RANGEFINDER_H__
