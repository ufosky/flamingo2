
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class Component;
typedef unsigned int ComponentType;
typedef unsigned int ComponentID;

#include "FL/Entity/Entity.h"
#include "FL/Event/Event.h"

#include <vector>

class Component {

    friend class EntityManager;

    public:
        Component(ComponentType type) : _type(type) {};
        virtual ~Component() {};

        Entity *entity;

    protected:
        ComponentType _type;
        ComponentID _id;
};

struct ComponentEvent : public EventData {
    ComponentEvent(EventType _type, Entity *_e, ComponentType _ctype) : EventData(_type), e(_e), ctype(_ctype) {};
    Entity *e;
    ComponentType ctype;
};

#endif

