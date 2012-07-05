
#include "FL/Flamingo.h"
#include "FL/Components/FLComponents.h"

#include "IL/il.h"

#include "physfs.h"

#include <iostream>

int Flamingo::_Init(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return -1;
    }

    // Initialize SDL_GL Attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
     
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
     
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
     
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    

    // Create window
    _displaySize = (SDL_Rect){0, 0, 1024, 768};
    if ((_display = SDL_SetVideoMode(_displaySize.w, _displaySize.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL) {
        return -1;
    }

    // OpenGL settings
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    glEnable(GL_TEXTURE_2D);

    // Flamingo
    PHYSFS_init(argv[0]);
    PHYSFS_mount(PHYSFS_getBaseDir(), "/", 0);
    ilInit();

    _eventManager = new EventManager();
    _entityManager = new EntityManager(_eventManager);
    inputSystem = new InputSystem(_eventManager, _entityManager);

    //// Screens
    screenSystem = new ScreenSystem(_eventManager, _entityManager);
	SDL_Rect r = {0, 100, 640, 240};

	Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new PositionComp());
	_entityManager->AddComponent(e, new ScreenComp(&_displaySize));

	e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new PositionComp());
	_entityManager->AddComponent(e, new ScreenComp(&r));
    //_entityManager->DestroyEntity(e);

    return this->Init(argc, argv);
}

void Flamingo::_Cleanup() {

    this->Cleanup();

    delete _entityManager;
    delete _eventManager;

    SDL_Quit();
}

