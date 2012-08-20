
#include "FL/Systems/InputSystem.h"
#include "FL/Components/FLComponents.h"

#include "SDL.h"

#include "FL/Events/FLInputKeys.h"

static SDL_Event sdl_event;

InputSystem::InputSystem(EventManager *eventManager, EntityManager *entityManager) : EntitySystem(eventManager, entityManager) {

    //_types.insert(FL_COMPTYPE_INPUT);
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
                    inputEventClass = PyObject_GetAttrString(scriptModule, "InputEvent");
                }
            }
        }

        Py_DECREF(scriptName);
        Py_XDECREF(scriptModule);
    }

    inputEventQueue = PyList_New(0);
}

InputSystem::~InputSystem() {

    Py_XDECREF(inputManager);
    Py_XDECREF(inputEventClass);
    Py_XDECREF(inputEventQueue);

}

bool InputSystem::ShouldProcess() {
    return true;
}

void InputSystem::Begin() {

    int inputType, inputKey;
    PyObject *event;

    while(SDL_PollEvent(&sdl_event)) {
        
        inputType = NOEVENT;
        inputKey = K_NONE;
        
        if (sdl_event.type == SDL_QUIT) {

            inputType = -2;
            inputKey = -2;
            quit = true;

        } else if (sdl_event.type == SDL_MOUSEMOTION) {

            inputType = MOUSEMOTION;
            inputKey = M_MOTION;

        } else if (sdl_event.type == SDL_MOUSEBUTTONDOWN) {

            inputType = MOUSEBUTTONDOWN;
            inputKey = sdl_event.button.button;

        } else if (sdl_event.type == SDL_MOUSEBUTTONUP) {
            
            inputType = MOUSEBUTTONUP;
            inputKey = sdl_event.button.button;
        
        } else if (sdl_event.type == SDL_KEYDOWN) {
            
            inputType = KEYDOWN;
            inputKey = sdl_event.key.keysym.sym;
        
        } else if (sdl_event.type == SDL_KEYUP) {
            
            inputType = KEYUP;
            inputKey = sdl_event.key.keysym.sym;
        
        } else {
           continue;
        }

        event = PyObject_CallFunction(inputEventClass, (char *)"ii", inputType, inputKey);
        if (event != NULL) {
            PyList_Append(inputEventQueue, event);
        }

        Py_XDECREF(event);
    }

    PyObject_CallMethod(inputManager, (char *)"process", (char *)"O", inputEventQueue);
    PySequence_DelSlice(inputEventQueue, 0, PySequence_Length(inputEventQueue));
}

void InputSystem::ProcessEntity(Entity *e) {

}

void InputSystem::End() {

}

