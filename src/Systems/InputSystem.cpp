
#include "FL/Systems/InputSystem.h"
#include "FL/Components/FLComponents.h"

#include "SDL.h"

static SDL_Event sdl_event;

InputSystem::InputSystem(EventManager *eventManager, EntityManager *entityManager) : EntitySystem(eventManager, entityManager) {

    _types.insert(FL_COMPTYPE_INPUT);
    quit = false;

    // Load Python module
    PyObject *scriptModule, *scriptName;

    scriptName = PyString_FromString("flamingo.inputmanager");
    if (scriptName != NULL) {
        scriptModule = PyImport_Import(scriptName);

        if (scriptModule != NULL) {
            PyObject *inputManagerClass = PyObject_GetAttrString(scriptModule, "InputManager");
            if (inputManagerClass != NULL) {

                inputManager = PyObject_CallFunction(inputManagerClass, NULL);
                if (inputManager != NULL) {
                    inputEvent = PyObject_GetAttrString(scriptModule, "inputevent");
                }
            }
        }

        Py_DECREF(scriptName);
        Py_XDECREF(scriptModule);
    }

    inputQueue = std::vector<PyObject *>();
}

InputSystem::~InputSystem() {

    Py_XDECREF(inputManager);
    Py_XDECREF(inputEvent);

}

bool InputSystem::ShouldProcess() {
    return true;
}


void InputSystem::Begin() {
    while(SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_QUIT) {
            quit = true;
        } else if (sdl_event.type == SDL_KEYDOWN && sdl_event.key.keysym.sym==SDLK_ESCAPE) {
            quit = true;
        }
    }
}

void InputSystem::ProcessEntity(Entity *e) {

}

void InputSystem::End() {

}

