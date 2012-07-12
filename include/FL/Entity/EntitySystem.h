
#ifndef _ENTITYSYSTEM_H_
#define _ENTITYSYSTEM_H_

#include "FL/Entity/EntityManager.h"
#include "FL/Event/Event.h"
#include "FL/Event/EventManager.h"

#include <set>

class EntitySystem : EventListener {

    public:
        EntitySystem(EventManager *eventManager, EntityManager *entityManager);
        virtual ~EntitySystem();

        void Process();
        bool HandleEvent(EventData *event);
    
    protected:

        virtual bool ShouldProcess() = 0;
        virtual void Begin() = 0;
        virtual void End() = 0;
        virtual void ProcessEntity(Entity *e) = 0;

        virtual bool HandleComponentAdd(Entity *e, ComponentType type) { return false; };
        virtual bool HandleComponentRemove(Entity *e, ComponentType type) { return false; };

        EventManager *_eventManager;
        EntityManager *_entityManager;
        std::set<Entity *> _active;
        std::set<ComponentType> _types;
};

#endif

