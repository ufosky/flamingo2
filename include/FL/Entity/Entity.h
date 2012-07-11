
#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity;
typedef unsigned int EntityID;

#include "eigen3/Eigen/Dense"

#include "FL/Entity/Component.h"
#include "FL/Entity/EntityManager.h"
#include "FL/Event/FLEvents.h"

#include <Python.h>

#include <map>
#include <set>


class Entity {

    friend class EntityManager;
    friend class Component;

    public:
        Entity(EntityID id) : pyEntity(NULL), _id(id) {};
        ~Entity();

        bool HasComponentType(ComponentType type);
        bool HasComponentTypes(std::set<ComponentType> types);


    protected:
        EntityID _id;
        unsigned int _index;
        std::set<ComponentType> _types;
        EntityManager *_entityManager;
        PyObject *pyEntity;

        void LoadPyEntity();
};

struct EntityEvent : public EventData {
    EntityEvent(EventType _type, Entity *_e) : EventData(_type), e(_e) {};
    Entity *e;
};

#endif

