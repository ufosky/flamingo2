
#include "FL/Flamingo.h"
#include "FL/Components/FLComponents.h"
#include "FL/FLUtility.h"

#include "IL/il.h"
#include "physfs.h"
#include <Python.h>

#include <iostream>

#define REGISTER_COMPONENT(NAME, TYPE) _entityManager->factory->RegisterComponent<NAME>(TYPE)

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

    std::cout << "PHYSFS Base Dir: " << PHYSFS_getBaseDir() << "\n";
    
    //// Python
    Py_Initialize();
    pythonDir = "python/";
    PHYSFS_mount(pythonDir.c_str(), "python", 0);
    AddPythonPath(pythonDir);

    _eventManager = new EventManager();
    _entityManager = new EntityManager(_eventManager);
    inputSystem = new InputSystem(_eventManager, _entityManager);

    _masterClock = new Clock();

    // Register Components
    REGISTER_COMPONENT(PositionComp, FL_COMPTYPE_POSITION);
    REGISTER_COMPONENT(ScreenComp, FL_COMPTYPE_SCREEN);
    REGISTER_COMPONENT(SpriteComp, FL_COMPTYPE_SPRITE);

    ScreenComp *_s = (ScreenComp *)_entityManager->factory->CreateInstance(FL_COMPTYPE_SCREEN);
    std::cout << _s->local_rect.x << "\n";

    //// Screens
    screenSystem = new ScreenSystem(_eventManager, _entityManager);
	SDL_Rect r = {0, 100, 640, 240};
	SDL_Rect r2 = {100, 200, 800, 480};

	Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new PositionComp());
    //ScreenComp *s = new ScreenComp(&_displaySize);
    ScreenComp *s = new ScreenComp(&r2);
    s->LoadScript("scripts/testscript.py", "testscript");
	_entityManager->AddComponent(e, s);

	e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new PositionComp());
	_entityManager->AddComponent(e, new ScreenComp(&r));
    //_entityManager->DestroyEntity(e);

    int res = this->Init(argc, argv);
    
    // Test DB dump
    _entityManager->Dump("database.db");
    
    return res;
}

void Flamingo::_Cleanup() {

    this->Cleanup();

    delete _entityManager;
    delete _eventManager;

    Py_Finalize();

    SDL_Quit();
}

