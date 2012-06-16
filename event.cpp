
#include "flamingo.h"

// Return -1 if execution should end
// Return 0 otherwise
//

SDL_Event sdl_event;

int Flamingo::handle_events() {

    while(SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_QUIT) {
            return -1;
        }
    }

    return 0;
}
