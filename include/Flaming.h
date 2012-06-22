
#ifndef FLAMINGO_H_
#define FLAMINGO_H_ 

#include <list>

#include <SDL/SDL.h>
#include <OpenGL/gl.h>

#include "Screen.h"

class Flamingo {

    private:

        bool _running;
        SDL_Surface *_display;
        SDL_Rect _display_size;
        
        std::list<Screen> screens;

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

