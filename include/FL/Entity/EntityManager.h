
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

class EntityManager;

#include "FL/Entity/Entity.h"
#include "FL/Entity/Component.h"
#include <map>
#include <set>
#include <vector>

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

		void RegisterComponentVector(ComponentType type, std::vector<Component *> *vect);
		void UnregisterComponentVector(ComponentType type);

        void Process();

    protected:
		void _DestroyEntities();
		void _DestroyComponents(Entity *e);
		void _DestroyComponent(Entity *e, ComponentType type);
		void _RemoveComponentFromRegisteredVector(ComponentType type, Component *comp);

        void _Process(Entity *e, Component *comp);
		int _RegisteredComponentVectorSearch(std::vector<Component *> *v, Component *comp);

        EntityID _nextID;
        std::map<Entity *, std::map<ComponentType, Component *> > _components;
        std::set<ComponentType> _processed;
		std::map<ComponentType, std::vector<Component *> *> _registeredComponentVectors;
};

#endif

