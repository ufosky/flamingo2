
#ifndef _EVENT_H_
#define _EVENT_H_

typedef unsigned int EventType;

class EventData {
    public:
        EventData(EventType _type) : type(_type) {};
        EventType type;
};

class EventListener {
    public:
        virtual ~EventListener() {};

        virtual bool HandleEvent(EventData const &data) = 0;
};

#endif

