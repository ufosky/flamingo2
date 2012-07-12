
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
        Entity(EntityID id) : _id(id), pyEntity(NULL) {};
        ~Entity();

        bool HasComponentType(ComponentType type);
        bool HasComponentTypes(std::set<ComponentType> types);
        Component *GetAs(ComponentType type);

        void AddComponent(Component *comp);
        void RemoveComponent(Component *comp);

    protected:
        EntityID _id;
        unsigned int _index;
        std::set<ComponentType> _types;
        EntityManager *_entityManager;
        PyObject *pyEntity;

        void LoadPyEntity();
};

class EntityEvent : public EventData {
    public:
        EntityEvent(EventType _type, Entity *_e) : EventData(_type), e(_e) {};
        Entity *e;
};

#endif

