#include "EventManager.h"

EventManager testInstance (10);

int blinkID;
int digitalReadID;
int digitalReadValue = 1;
int analogReadID;
int analogReadValue = 1;

void setup()  {
    Serial.begin(115200);

    pinMode(9, OUTPUT);
    pinMode(10, INPUT_PULLUP);
    pinMode(A0, INPUT);

    // Setup Events
    blinkID = testInstance.oscillateEvery(9, 100, LOW);
    digitalReadID = testInstance.digitalReadEvery(10, 50, &digitalReadValue);
    analogReadID = testInstance.analogReadEvery(A0, 150, &analogReadValue);
}

void loop()  {
    // Do stuff with those events
    Serial.print("DIGITAL VALUE:");
    Serial.println(digitalReadValue);
    Serial.print("ANALOG VALUE: ");
    Serial.println(analogReadValue);

    // If we read true on the button stop the blinkID event
    if (digitalReadValue == 0)  {
        testInstance.stop(blinkID);
        digitalWrite(9, LOW);
        blinkID = -1;
    } else if (digitalReadValue == 1 && blinkID == -1) {
        blinkID = testInstance.oscillateEvery(9, 100, LOW);
    }

    testInstance.update();
}
