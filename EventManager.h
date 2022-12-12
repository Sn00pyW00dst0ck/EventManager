#include <inttypes.h>
#include <Arduino.h>

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
        template<typename ...Arguments>
        void (*callback)(...Arguments);
        Event(void);

        void update(void);
        void update(unsigned long now);
    };

    EventManager::Event _events[10];
    int8_t findFreeEventIndex(void);

    public:

    int8_t executeEvery(unsigned long period, void (*callback)(void));
    int8_t executeEvery(unsigned long period, void (*callback)(void), int repeatCount);
    int8_t executeAfter(unsigned long duration, void (*callback)(void));
    int8_t oscillateEvery(uint8_t pin, unsigned long period, uint8_t startingValue);
    int8_t oscillateEvery(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount);
    int8_t readEvery();
    
    void stop(int8_t id);
    void update(void);
    void update(unsigned long now);
};
