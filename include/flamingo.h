
#ifndef FLAMINGO_H_
#define FLAMINGO_H_ 

#include <list>

#include <SDL/SDL.h>
#include <OpenGL/gl.h>

#include "Screen.h"

class Flamingo {

    private:

        bool running;
        SDL_Surface *Surf_display;
        SDL_Rect display_size;
        
        std::list<Screen> screens;

    public:
        Flamingo();
        ~Flamingo();

        int execute();

        int init();
        int handle_events();
        void step();
        void render();
        void cleanup();

        void push_screen(Screen &screen);
        void remove_screen(Screen &screen);
};

#endif

