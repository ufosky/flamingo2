
#include "flamingo.h"

int Flamingo::init() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return -1;
    }

    if ((Surf_display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return -1;
    }

    return 0;
}

void Flamingo::cleanup() {

    SDL_Quit();

}
