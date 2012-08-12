
#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "FL/Entity/EntitySystem.h"
#include "Python.h"

#include <vector>

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

        PyObject *inputManager, *inputEvent;
        std::vector<PyObject *> inputQueue;
};

#endif

