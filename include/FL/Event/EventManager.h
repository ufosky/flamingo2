
#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include "FL/Event/Event.h"

#include <list>
#include <map>

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
        
    protected:

        typedef std::list<EventListener * > EventListenerList;
        typedef std::map<EventType, EventListenerList > EventListenerMap;
        typedef std::pair<EventType, EventListenerList > EventListenerPair;

        EventListenerMap _listeners;
        EventListenerList _globals;
};

#endif

