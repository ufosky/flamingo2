
#include "FL/Components/ScreenComp.h"
#include <OpenGL/gl.h>

ScreenComp::ScreenComp() {
	_SetType();
    local_rect = (SDL_Rect){0, 0, 1024, 648};
    bound_rect << local_rect.x, local_rect.x + local_rect.w, local_rect.x + local_rect.w, local_rect.x,
                  local_rect.y, local_rect.y, local_rect.y + local_rect.h, local_rect.y + local_rect.h,
                  0, 0, 0, 0;
}

ScreenComp::ScreenComp(SDL_Rect *screen) {
	_SetType();
    local_rect = *screen;
    bound_rect << screen->x, screen->x + screen->w, screen->x + screen->w, screen->x,
                  screen->y, screen->y, screen->y + screen->h, screen->y + screen->h,
                  0, 0, 0, 0;
}

ScreenComp::ScreenComp(SDL_Rect *screen, Eigen::Matrix<float, 4, 3> *bound) {
	_SetType();
    local_rect = *screen;
    bound_rect = *bound;
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

