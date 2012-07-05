
#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity;
typedef unsigned int EntityID;

#include "FL/Entity/Component.h"
#include "FL/Entity/EntityManager.h"
#include "FL/Event/FLEvents.h"

#include <map>
#include <set>


class Entity {

    friend class EntityManager;

    public:
        Entity(EntityID id) : _id(id) {};
        ~Entity();

        bool HasComponentType(ComponentType type);
        bool HasComponentTypes(std::set<ComponentType> types);

    protected:
        EntityID _id;
        unsigned int _index;
        std::set<ComponentType> _types;
        EntityManager *_entityManager;
};

struct EntityEvent : public EventData {
    EntityEvent(EventType _type, Entity *_e) : EventData(_type), e(_e) {};
    Entity *e;
};

#endif

