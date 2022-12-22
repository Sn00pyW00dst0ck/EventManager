#include <EventManager.h>

EventManager riderManager (15);

// Set constants for pins and globals
const int ledPins[] = { 8, 9, 10, 11, 12, 13 };
const int lightOnTime = 150; // Higher number means each LED is on longer
int currentLED = 0;

// Function headers
void lineRideOnce();
typedef void (*evt)(void);  // typedef so we can return a void function from another function
evt getCorrectOscillationEvent();

void setup()  {
    // Set LED pin modes to OUTPUT
    for (int i = 0; i < 6; i++)  {
        pinMode(ledPins[i], OUTPUT);
    }
    
    // Have the riderManager execute one 'line ride' every X millis
    riderManager.executeEvery((10 * lightOnTime), lineRideOnce);
    lineRideOnce(); // call the line rider to start so we aren't waiting for 10 * lightOnTime for first run
}

void loop()  {
    // Tell the manager to update
    riderManager.update();
}

void lineRideOnce()  {
    // For Loop of execution events for going up
    for (currentLED = 0; currentLED < 6; currentLED++)  {
        // We can't just use the value of 'currentLED' to set the oscillationEvery event pin 
        // because the value of currentLED would change before the event was executed and the
        // manager would blink the wrong LED. The getCorrectOscillationEvent() function takes
        // the currentLED and generates an oscillationEvery event using a constant instead of the variable.
        riderManager.executeAfter(currentLED * lightOnTime, getCorrectOscillationEvent());
    }

    // For Loop of execution events for going down
    for (currentLED = 4; currentLED > 0; currentLED--)  {
        riderManager.executeAfter((10 - currentLED) * lightOnTime, getCorrectOscillationEvent());
    }
}

evt getCorrectOscillationEvent()  {
    switch (currentLED)  {
        case 0:
            return []()  { 
                riderManager.oscillateEvery(ledPins[0], lightOnTime, LOW, 1); 
            };
        case 1:
            return []()  { 
                riderManager.oscillateEvery(ledPins[1], lightOnTime, LOW, 1); 
            };
        case 2:
            return []()  { 
                riderManager.oscillateEvery(ledPins[2], lightOnTime, LOW, 1); 
            };
        case 3:
            return []()  { 
                riderManager.oscillateEvery(ledPins[3], lightOnTime, LOW, 1); 
            };
        case 4:
            return []()  { 
                riderManager.oscillateEvery(ledPins[4], lightOnTime, LOW, 1); 
            };
        case 5:
            return []()  { 
                riderManager.oscillateEvery(ledPins[5], lightOnTime, LOW, 1); 
            };
    }
}
