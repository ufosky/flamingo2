
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

class EntityManager;

#include "FL/Entity/Entity.h"
#include "FL/Entity/Component.h"
#include <map>
#include <set>

class EntityManager {

    public:
        EntityManager();
        ~EntityManager();

        Entity *CreateEntity();
        void DestroyEntity(Entity *e);

        void AddComponent(Entity *e,Component *comp);
        void RemoveComponent(Entity *e, ComponentType type);
        void RemoveComponent(Entity *e, Component *comp);

        Component *GetComponent(Entity *e, ComponentType type);

        void Process();

    protected:
        void _Process(Entity *e, Component *comp);

        EntityID _nextID;
        std::map<Entity *, std::map<ComponentType, Component *> > _components;
        std::set<ComponentType> _processed;
};

#endif

