
%module entitymanager
%{
#include "FL/Entity/EntityManager.h"
%}

class EntityManager {

    public:
        EntityManager(EventManager *eventManager);
        ~EntityManager();

        Entity *CreateEntity();
        void DestroyEntity(Entity *e);

        void AddComponent(Entity *e,Component *comp);
        void RemoveComponent(Entity *e, Component *comp);
        void RemoveAllComponents(Entity *e, ComponentType type);

        const std::vector<Component *> &GetComponents(Entity *e, ComponentType type);
        Component *GetComponent(Entity *e, ComponentType type);
};

