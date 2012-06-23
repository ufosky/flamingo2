
#ifndef FLAMINGO_H_
#define FLAMINGO_H_ 

#include <list>

#include <SDL/SDL.h>
#include <OpenGL/gl.h>


#include "FL/Entity/EntityManager.h"
#include "FL/Screen.h"

class Flamingo {

    private:

        bool _running;

        EntityManager _entityManager;

        SDL_Surface *_display;
        SDL_Rect _displaySize;
        std::list<Screen> _screens;

    public:
        Flamingo();
        ~Flamingo();

        int Execute();

        int Init();
        int HandleEvents();
        void Step();
        void Render();
        void Cleanup();

        void PushScreen(Screen &screen);
        void RemoveScreen(Screen &screen);
};

#endif

