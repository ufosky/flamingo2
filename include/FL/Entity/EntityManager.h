
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

class EntityManager;

#include "FL/Entity/Entity.h"
#include "FL/Entity/Component.h"
#include "FL/Event/EventManager.h"

#include <map>
#include <set>
#include <vector>

class EntityManager {

    public:
        EntityManager(EventManager *eventManager);
        ~EntityManager();

        Entity *CreateEntity();
        void DestroyEntity(Entity *e);

        void AddComponent(Entity *e,Component *comp);
        void RemoveComponent(Entity *e, ComponentType type);
        void RemoveComponent(Entity *e, Component *comp);
        void RemoveAllComponents(Entity *e);
        void RemoveAllComponents(Entity *e, ComponentType type);

        const std::vector<Component *> &GetComponents(Entity *e, ComponentType type);
        Component *GetComponent(Entity *e, ComponentType type);

    protected:

        void _RemoveAllComponents(Entity *e, ComponentType type);

        static std::vector<Component *> EmptyList;

        EntityID _nextID;
        std::vector<unsigned int> _removedIndices;
        std::vector<Entity *> _entities;
        std::vector<std::vector<std::vector<Component *> > > _components;

        EventManager *_eventManager;
};

#endif

