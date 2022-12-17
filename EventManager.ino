#include "EventManager.h"

EventManager testInstance;

int blinkID;
int digitalReadID;
int digitalReadValue;
int analogReadID;
int analogReadValue;

void setup()  {
    Serial.begin(115200);

    pinMode(9, OUTPUT);
    pinMode(10, INPUT);
    pinMode(A0, INPUT);

    // Setup Events
    blinkID = testInstance.oscillateEvery(9, 100, LOW);
    digitalReadID = testInstance.digitalReadEvery(10, 50, &digitalReadValue);
    analogReadID = testInstance.analogReadEvery(A0, 150, &analogReadValue);
}

void loop()  {
    // Do stuff with those events
    Serial.println("DIGITAL VALUE:");
    Serial.println(digitalReadValue);
    Serial.print("ANALOG VALUE: ");
    Serial.println(analogReadValue);

    // If we read true on the button stop the blinkID event
    if (digitalReadValue == true)  {
        testInstance.stop(blinkID);
        digitalWrite(9, LOW);
    }

    testInstance.update();
}
