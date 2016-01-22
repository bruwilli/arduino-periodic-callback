# arduino-periodic-callback
Class that can call a callback function periodically

##Example usage
Write time since last callback to serial monitor everY 500ms, stopping on 4th callback
```
#include <PeriodicCallback.h>    

void callback(unsigned long timeElapsed) {
  static unsigned int timesCalled = 0;
  Serial.print("Callback called.  Time since last callback: ");
  Serial.println(timeElapsed);
  if (++timesCalled == 4) {
    myCallback.stop();
  }
}

PeriodicCallback myCallback(500, callback);
void setup() {
  myCallback.start();
}
void loop() {
  myCallback.update(); // Must be called in loop.  Do not block (use delays) during loop
}
```
