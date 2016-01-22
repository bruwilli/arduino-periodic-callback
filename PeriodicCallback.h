/*
 * PeriodicCallback.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Bruce Williams
 */

#ifndef PeriodicCallback_H_
#define PeriodicCallback_H_
#include "Arduino.h"

// Example usage (write time since last callback to serial monitor ever 500ms, stop on 4th callback):
//
//    #include <PeriodicCallback.h>    
//
//    void callback(unsigned long timeElapsed) {
//      static unsigned int timesCalled = 0;
//      Serial.print("Callback called.  Time since last callback: ");
//      Serial.println(timeElapsed);
//      if (++timesCalled == 4) {
//        myCallback.stop();
//      }
//    }
//
//    PeriodicCallback myCallback(500, callback);
//    void setup() {
//      myCallback.start();
//    }
//    void loop() {
//      myCallback.update(); // Must be called in loop.  Do not block (use delays) during loop
//    }

class PeriodicCallback {
private:
  unsigned long mPeriod;
  unsigned long mStartTime;
  unsigned long mLastTime;
  void (*mCallbackFunction)(unsigned long const);


public:
  PeriodicCallback(): mPeriod(0), mStartTime(0), mLastTime(0), mCallbackFunction(NULL) {}; 
  PeriodicCallback(unsigned long const period, void (*callbackFunction)(unsigned long const)): 
    mPeriod(period), mCallbackFunction(callbackFunction), mStartTime(0), mLastTime(0){};

  // Use new period.  Will take effect immediately if this is running.  Note that the actual period
  // may be approximate, depending on how much time is spent in other parts of the run loop
  void setPeriod(unsigned long const period) { mPeriod = period; };

  // Use new callback.  Will take effect immediately if this is running.  Callback function should
  // take an unsigned long parameter which will be the time since the last time the callback function
  // was called; this parameter's value will be at least the callback period, but may be greater if
  // too much time is spent in other parts of the run loop.
  void setCallback(void (*callbackFunction)(unsigned long const)) { mCallbackFunction = callbackFunction; };

  void start(); // Start (or restart) the timer for this periodic callback
  void stop(); // Stop calling the callback
  
  // This is the workhorse function.  It must be called in your loop,
  // and your loop should be non-blocking (no delays)
  void update();
};

#endif /* PeriodicCallback_H_ */
