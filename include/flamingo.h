
#include <SDL/SDL.h>
#include <OpenGL/gl.h>

class Flamingo {

    private:

        bool running;

        SDL_Surface *Surf_display;

    public:
        Flamingo();

        int execute();

        int init();
        int handle_events();
        void step();
        void render();
        void cleanup();
};
