
#ifndef _SCREENSYSTEM_H_
#define _SCREENSYSTEM_H_

#include "FL/Entity/EntitySystem.h"

class ScreenSystem : public EntitySystem {

    public:
        ScreenSystem(EventManager *eventManager, EntityManager *entityManager);
        ~ScreenSystem();
        
    protected:
        bool ShouldProcess();
        void Begin();
        void End();
        void ProcessEntity(Entity *e);

        bool HandleComponentAdd(Entity *e, ComponentType type);
        bool HandleComponentRemove(Entity *e, ComponentType type);

        std::set<Entity *> _sprites;
};

#endif

