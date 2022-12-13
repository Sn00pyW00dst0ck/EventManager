#ifndef event_manager
#define event_manager

#include <inttypes.h>
#include <Arduino.h>

#define EVENT_NONE 0
#define EVENT_EVERY 1
#define EVENT_OSCILLATE 2
#define EVENT_DIGITAL_READ 3
#define EVENT_ANALOG_READ 4
#define MAX_NUMBER_OF_EVENTS 10
#define TIMER_NOT_AN_EVENT -2
#define NO_TIMER_AVAILABLE -1

class EventManager  {
    private:

    class Event  {
        public:
        uint8_t eventType;
        
        uint8_t pin;
        uint8_t pinState;
        
        unsigned long lastEventTime;
        unsigned long period;

        int count;
        int repeatCount;

        // callback
        void (*callback)(void);

        Event(void);

        void update(void);
        void update(unsigned long now);
    };

    EventManager::Event _events[MAX_NUMBER_OF_EVENTS];
    int8_t findFreeEventIndex(void);

    public:

    int8_t executeEvery(unsigned long period, void (*callback)(void));
    int8_t executeEvery(unsigned long period, void (*callback)(void), int repeatCount);
    int8_t executeAfter(unsigned long duration, void (*callback)(void));

    void stop(int8_t id);
    void update(void);
    void update(unsigned long now);
};

#endif