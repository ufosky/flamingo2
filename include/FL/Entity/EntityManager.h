
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

class EntityManager;

#include "FL/Entity/Entity.h"
#include "FL/Entity/Component.h"
#include <map>

class EntityManager {

    public:
        EntityManager();
        ~EntityManager();

        Entity *CreateEntity();
        void DestroyEntity();

        void AddComponent(Component *comp);
        void RemoveComponent(Component *comp);
        void RemoveComponents(ComponentType type);

        void GetComponents(Entity *e, ComponentType type);

        void Process();

    protected:
        void _Process(ComponentType type);

        std::map<Entity *, std::map<ComponentType, Component *> > _components;
};

#endif

