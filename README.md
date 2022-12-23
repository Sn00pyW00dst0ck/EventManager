# EventManager

Use this Event Manager to easily schedule concurrent events on an Arduino.

Here is a sample code:
```cpp
#include <EventManager.h>

EventManager blinkManager (10);

int blinkID;
int digitalReadID;
int digitalReadValue = 1;

void setup()  {
    Serial.begin(115200);

    pinMode(9, OUTPUT);
    pinMode(10, INPUT_PULLUP);

    // Setup Events
    blinkID = blinkManager.oscillateEvery(9, 100, LOW);
    digitalReadID = blinkManager.digitalReadEvery(10, 50, &digitalReadValue);
}

void loop()  {
    // Print our digital read value to the serial
    Serial.print("DIGITAL VALUE:");
    Serial.println(digitalReadValue);

    // If we read true on the button stop the blinkID event
    if (digitalReadValue == 0)  {
        blinkManager.stop(blinkID);
        digitalWrite(9, LOW);
        blinkID = -1;
    } else if (digitalReadValue == 1 && blinkID == -1) {
        blinkID = blinkManager.oscillateEvery(9, 100, LOW);
    }

    // Tell the manager to update
    blinkManager.update();
}
```

## EventManager Class Public Methods Documentation

`executeEvery` creates a new event which will execute a given void function every X millis.

`executeAfter` creates a new event which will execute a given void function one time after X millis have passed.

`oscillateEvery` creates a new event which will swap the state of a pin from HIGH to LOW or vice versa every X millis.

`digitalReadEvery` creates a new event which will digital read a given pin every X millis and store the result in a provided variable.

`digitalReadAfter` creates a new event which will digital read a given pin after X millis and store the result in a provided variable.

`analogReadEvery` creates a new event which will analog read a given pin every X millis and store the result in a provided variable.

`analogReadAfter` creates a new event which will analog read a given pin after X millis and store the result in a provided variable.

`stop` will cause the event with given event id to stop execution.

`update` will cause the event manager to update and check for any events that need to execute.
