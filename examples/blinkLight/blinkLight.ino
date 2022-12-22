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
