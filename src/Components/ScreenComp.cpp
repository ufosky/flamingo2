
#include "FL/Components/ScreenComp.h"
#include <OpenGL/gl.h>

ScreenComp::ScreenComp() {
	_SetType();
    local_rect = (SDL_Rect){0, 0, 1024, 648};
}

ScreenComp::ScreenComp(SDL_Rect *screen) {
	_SetType();
    local_rect = *screen;
}

ScreenComp::~ScreenComp() {

}

void ScreenComp::Init() {

}

void ScreenComp::Process() {

}

void ScreenComp::Cleanup() {

}

void ScreenComp::Draw() {
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex2f(0, 0);
        glColor3f(1, 1, 0); glVertex2f(local_rect.w, 0);
        glColor3f(1, 0, 1); glVertex2f(local_rect.w, local_rect.h);
        glColor3f(1, 1, 1); glVertex2f(0, local_rect.h);
    glEnd();
}

