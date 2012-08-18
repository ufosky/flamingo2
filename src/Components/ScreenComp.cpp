
#include "FL/Components/ScreenComp.h"

#include <OpenGL/gl.h>
#include <sqlite3.h>

ScreenComp::ScreenComp() : Component(FL_COMPTYPE_SCREEN) {
    local_rect = (SDL_Rect){0, 0, 1024, 648};
}

ScreenComp::ScreenComp(SDL_Rect *screen) : Component(FL_COMPTYPE_SCREEN) {
    local_rect = *screen;
}

ScreenComp::~ScreenComp() {

}

char *ScreenComp::Columns() {
    return (char *)", x int, y int, w int, h int";
}

char *ScreenComp::DumpRow() {
    return sqlite3_mprintf(", %d, %d, %d, %d", local_rect.x, local_rect.y, local_rect.w, local_rect.h);
}

