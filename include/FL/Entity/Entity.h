
#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity;
typedef unsigned int EntityID;

#include "FL/Entity/Component.h"
#include "FL/Entity/EntityManager.h"
#include <map>


class Entity {

    friend class EntityManager;

    public:
        Entity(EntityID id);
        ~Entity();

        bool HasComponentType(ComponentType type);
        Component *GetAs(ComponentType type);

    protected:
        EntityID _id;
        std::map<ComponentType, Component *> _components;
        EntityManager *_entityManager;
};

#endif

