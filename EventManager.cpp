/**
 * 
 * 
 * 
 * 
*/

#include "EventManager.h"

EventManager::Event::Event(void)  {
    this->eventType = EVENT_NONE;
}

void EventManager::Event::update(void)  {
    this->update(millis());
}

void EventManager::Event::update(unsigned long now)  {
	// Check if event should update
    if (now - this->lastEventTime >= period)  {
		// Do different stuff for different events
		switch (eventType)  {
			case EVENT_EVERY:
				(*this->callback)();
				break;
			case EVENT_OSCILLATE:
				this->pinState = !this->pinState;
				digitalWrite(this->pin, this->pinState);
				break;
            case EVENT_DIGITAL_READ:

                break;
            case EVENT_ANALOG_READ:

                break;
			case EVENT_NONE:
				return;
		}
		this->lastEventTime = now;
		this->count++;
	}
	// Check if we did the event the number of requested times
	if (this->repeatCount > -1 && this->count >= this->repeatCount)  {
		this->eventType = EVENT_NONE;
	}
}

int8_t EventManager::executeEvery(unsigned long period, void (*callback)(void))  {
    return this->executeEvery(period, callback, -1);
}

int8_t EventManager::executeEvery(unsigned long period, void (*callback)(void), int repeatCount)  {
    int8_t i = findFreeEventIndex();
	if (i == NO_TIMER_AVAILABLE) return NO_TIMER_AVAILABLE;

	// Set the event properties for executing every X millis
	this->_events[i].eventType = EVENT_EVERY;
	this->_events[i].period = period;
	this->_events[i].repeatCount = repeatCount;
	this->_events[i].callback = callback;
	this->_events[i].lastEventTime = millis();
	this->_events[i].count = 0;
	return i;
}

int8_t EventManager::executeAfter(unsigned long duration, void (*callback)(void))  {
    return this->executeEvery(duration, callback, 1);
}

void EventManager::stop(int8_t id)  {
	// Stop the requested event from happening from now on
    if (id >= 0 && id < MAX_NUMBER_OF_EVENTS) {
		this->_events[id].eventType = EVENT_NONE;
	}
}

void EventManager::update(void)  {
    unsigned long now = millis();
	this->update(now);
}

void EventManager::update(unsigned long now)  {
	// Update all the events with the given time in millis
    for (int8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)  {
		if (this->_events[i].eventType != EVENT_NONE)  {
			this->_events[i].update(now);
		}
	}
}

int8_t EventManager::findFreeEventIndex(void)  {
	// Find an event listed as NONE and return it for use later
	for (int8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)  {
		if (this->_events[i].eventType == EVENT_NONE)  {
			return i;
		}
	}
	return NO_TIMER_AVAILABLE;
}
