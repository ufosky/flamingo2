
#include "FL/Systems/InputSystem.h"
#include "FL/Components/FLComponents.h"

#include "SDL.h"

static SDL_Event sdl_event;

InputSystem::InputSystem(EventManager *eventManager, EntityManager *entityManager) : EntitySystem(eventManager, entityManager) {

    _types.insert(FL_COMPTYPE_INPUT);
    quit = false;
}

InputSystem::~InputSystem() {

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

