
#include "FL/Flamingo.h"

#include "FL/Components/TestComponent.h"

int Flamingo::Init() {

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
    //// Entity Manager
    _entityManager = new EntityManager();

    // Test
    Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new TestComponent());

    //// Screens
    Screen s = Screen(&_displaySize);
    _screens = std::list<Screen>();
    _screens.push_back(s);

    SDL_Rect r = {0, 240, 640, 240};
    s = Screen(&r);
    _screens.push_back(s);

    return 0;
}

void Flamingo::Cleanup() {

    delete _entityManager;

    SDL_Quit();

}

