
#include "FL/Event/EventManager.h"


EventManager::EventManager() {

}

EventManager::~EventManager() {

    RemoveAllListeners();
}

void EventManager::AddListener(EventListener *listener, EventType type) {

    EventListenerMap::iterator it = _listeners.find(type);
    if (it == _listeners.end()) {
        it = _listeners.insert(EventListenerPair(type, EventListenerList())).first;
    }

    it->second.push_back(listener);
}

void EventManager::RemoveListener(EventListener *listener, EventType type) {

    EventListenerMap::iterator it = _listeners.find(type);
    if (it == _listeners.end()) {
        return;
    }
    
    for (EventListenerList::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {

        if (*it2 == listener) {
            it->second.erase(it2);
            return;
        }
    }
}

void EventManager::AddGlobalListener(EventListener *listener) {
    _globals.push_back(listener);
}

void EventManager::RemoveGlovalListener(EventListener *listener) {

    for(EventListenerList::iterator it = _globals.begin(); it != _globals.end(); it++) {
        if (*it == listener) {
            _globals.erase(it);
            return;
        }
    }
}

void EventManager::RemoveAllListeners() {

    for (EventListenerMap::iterator it = _listeners.begin(); it != _listeners.end(); it++) {
        it->second.clear();
    }

    _listeners.clear();
    _globals.clear();
}

void EventManager::FireEvent(EventData *event) {


    for (EventListenerList::const_iterator it = _globals.begin(); it != _globals.end(); it++) {
        if ((*it)->HandleEvent(event)) {
            return;
        }
    }

    EventListenerMap::iterator it = _listeners.find(event->type);
    if (it == _listeners.end()) {
        return;
    }

    for (EventListenerList::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
        if ((*it2)->HandleEvent(event)) {
            return;
        }
    }
}

