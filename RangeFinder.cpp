#include "Arduino.h"
#include "RangeFinder.h"

RangeFinder::RangeFinder(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(echoPin, LOW);
  pinMode(echoPin, INPUT);
  RangeFinder::_triggerPin = triggerPin;
  RangeFinder::_echoPin = echoPin;
}

RangeFinder::RangeFinder(int triggerPin, int echoPin, int minRange, int maxRange)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(echoPin, LOW);
  pinMode(echoPin, INPUT);
  RangeFinder::_triggerPin = triggerPin;
  RangeFinder::_echoPin = echoPin;
  RangeFinder::_minRange = minRange;
  RangeFinder::_maxRange = maxRange;
}

// This code sends a "ping", similar
// to submarine sonar or a bat sonar,
// to determine the range of an object.
unsigned long RangeFinder::pingRange()
{
  RangeFinder::_pingTime = 999999;
  if(!digitalRead(RangeFinder::_echoPin)) {
    digitalWrite(RangeFinder::_triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(RangeFinder::_triggerPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(RangeFinder::_triggerPin, LOW);
    delayMicroseconds(5);
  
    RangeFinder::_pingTime = pulseIn(RangeFinder::_echoPin, HIGH);
    rf_debugPrint(2, "duration => ", RangeFinder::_pingTime);
    if(_pingTime == 0) return 999999;
  } else delay(25);
  return RangeFinder::_pingTime;
}


// This code sends a "ping", similar
// to submarine sonar or a bat sonar,
// to determine the range of an object.
unsigned long RangeFinder::pingRange(unsigned long to)
{

  RangeFinder::_pingTime = 999999;
  if(!digitalRead(RangeFinder::_echoPin)) {
    digitalWrite(RangeFinder::_triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(RangeFinder::_triggerPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(RangeFinder::_triggerPin, LOW);
    delayMicroseconds(5);
  
    RangeFinder::_pingTime = pulseIn(RangeFinder::_echoPin, HIGH, to);
    rf_debugPrint(2, "duration => ", RangeFinder::_pingTime);
    if(RangeFinder::_pingTime == 0) return 999999;
  } else delay(25);
checkRangeDone:
  return RangeFinder::_pingTime;
}

float RangeFinder::distanceInMillimeters()
{
  return (float)(RangeFinder::_pingTime * 0.172);
}

void RangeFinder::filterRangeMillimeters(void) {
  unsigned long lrange,s1,s2,s3;

    s1 = RangeFinder::pingRange(50000);
    delay(50);
    s2 = RangeFinder::pingRange(50000);
    delay(50);
    s3 = RangeFinder::pingRange(50000);

    lrange = 999999.0;
    if(s1 == s2 || s1 == s3) 
       lrange = s1;
    if(s2 == s3) 
      lrange = s2;

    if(s1 != s2 && s1 != s3 && s2 != s3) {
       if(s1 < s2 && s2 < s3) lrange = s2;
       if(s3 < s2 && s2 < s1) lrange = s2;
       if(s2 < s1 && s1 < s3) lrange = s1;
       if(s3 < s1 && s1 < s2) lrange = s1;
       if(s2 < s3 && s3 < s1) lrange = s3;
       if(s1 < s3 && s3 < s2) lrange = s3;
    }

    RangeFinder::_pingTime = lrange;
}
