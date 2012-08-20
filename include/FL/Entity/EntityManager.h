
#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

class EntityManager;

#include "FL/Entity/Entity.h"
#include "FL/Entity/Component.h"
#include "FL/Entity/ComponentFactory.h"
#include "FL/Event/EventManager.h"

#include <map>
#include <set>
#include <vector>
#include <string>

#include <sqlite3.h>
#include "physfs.h"

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

        int Dump(std::string file);
        int Load(std::string file);

        ComponentFactory *factory;

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

