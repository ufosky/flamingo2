
#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

#include "FL/Entity/EntitySystem.h"

class InputSystem : public EntitySystem {

    public:
        InputSystem(EventManager *eventManager, EntityManager *entityManager);
        ~InputSystem();

        bool quit;
        
    protected:
        bool ShouldProcess();
        void Begin();
        void End();
        void ProcessEntity(Entity *e);
};

#endif

