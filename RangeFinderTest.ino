#include "RangeFinder.h"

#define RangeTrig 8
#define RangeEcho 7

//#undef _DEBUG_
#define _DEBUG_

#ifndef _DEBUG_
int debug_lvl = 0;
#else
int debug_lvl = 1;
#endif

// A place to remember the current range
float range = 0.0;

// NOTE: The define here creates
//       a method for controling
//       debug output so we can
//       turn it off simply by
//       undefining the above
//       variable, "_DEBUG_"
#define debugPrint(lvl,s,val) \
        if (debug_lvl >= lvl) { \
          Serial.print(s); \
          Serial.println((float)val); \
        }


RangeFinder *rf;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Pin setup...");
  rf = new RangeFinder(RangeTrig, RangeEcho);
}

void loop() {
  // put your main code here, to run repeatedly:
  //range = findRange();
  rf->filterRangeMillimeters();
  range = rf->distanceInMillimeters();
  if(range < 100.0) {
    debugPrint(0, "Too close =>", range);
  }
  if(range > 100.0 && range < 500.0) {
    debugPrint(0, "    close =>", range);
  }
  if(range > 500.0)
    debugPrint(0, "      far => ", range);
}
