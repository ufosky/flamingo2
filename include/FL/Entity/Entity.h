
#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity;

#include "FL/Entity/Component.h"
#include "FL/Entity/EntityManager.h"
#include <map>

typedef unsigned int EntityID;

class Entity {

    friend class EntityManager;

    public:
        ~Entity();

        bool HasComponentType(ComponentType type);
        Component *GetAs(ComponentType type);

    protected:
        EntityID _id;
        std::map<ComponentType, Component *> _components;
        EntityManager *_entityManager;
};

#endif

