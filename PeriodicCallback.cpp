/*
 * PeriodicCallback.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Bruce Williams
 */

#include "PeriodicCallback.h"

void PeriodicCallback::start() {
  if (mCallbackFunction && mPeriod) {
    mStartTime = mLastTime = millis();
  }
}
void PeriodicCallback::stop() {
  mStartTime = 0;
}

// This is the workhorse function.  It must be called in your loop,
// and your loop should be non-blocking (no delays)
void PeriodicCallback::update() {
  if (mStartTime && mCallbackFunction) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - mStartTime;
    if (elapsedTime >= mPeriod) {
      mCallbackFunction(currentTime - mLastTime);
      mLastTime = currentTime;
      mStartTime = currentTime - (elapsedTime % mPeriod);
    }
  }
}
