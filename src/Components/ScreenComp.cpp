
#include "FL/Components/ScreenComp.h"

#include <OpenGL/gl.h>

ScreenComp::ScreenComp() : Component(FL_COMPTYPE_SCREEN) {
    local_rect = (SDL_Rect){0, 0, 1024, 648};
}

ScreenComp::ScreenComp(SDL_Rect *screen) : Component(FL_COMPTYPE_SCREEN) {
    local_rect = *screen;
}

ScreenComp::~ScreenComp() {

}

