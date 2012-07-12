
%module eventmanager
%{
#include "FL/Event/EventManager.h"
%}

typedef unsigned int EventType;

class EventData {
    public:
        EventData(EventType _type) : type(_type) {};
        EventType type;
};

class EventListener {
    public:
        virtual ~EventListener() {};

        virtual bool HandleEvent(EventData *data) = 0;
};

class EventManager {
    public:
        EventManager();
        ~EventManager();

        void AddListener(EventListener *listener, EventType type);
        void RemoveListener(EventListener *listener, EventType type);

        void AddGlobalListener(EventListener *listener);
        void RemoveGlovalListener(EventListener *listener);

        void RemoveAllListeners();

        void FireEvent(EventData *event);
};

