
#include <OpenGL/gl.h>
#include "Screen.h"

Screen::Screen() {

    local_rect = (SDL_Rect){0, 0, 640, 480};
    bound_rect << local_rect.x, local_rect.x + local_rect.w, local_rect.x + local_rect.w, local_rect.x,
                  local_rect.y, local_rect.y, local_rect.y + local_rect.h, local_rect.y + local_rect.h,
                  0, 0, 0, 0;

}

Screen::Screen(SDL_Rect *screen) {

    local_rect = *screen;
    bound_rect << screen->x, screen->x + screen->w, screen->x + screen->w, screen->x,
                  screen->y, screen->y, screen->y + screen->h, screen->y + screen->h,
                  0, 0, 0, 0;

}

Screen::Screen(SDL_Rect *screen, Eigen::Matrix<float, 4, 3> *bound) {

    local_rect = *screen;
    bound_rect = *bound;

}

Screen::~Screen() {

}

void Screen::load_identity() {

}

void Screen::draw() {
    
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex2f(0, 0);
        glColor3f(1, 1, 0); glVertex2f(local_rect.w, 0);
        glColor3f(1, 0, 1); glVertex2f(local_rect.w, local_rect.h);
        glColor3f(1, 1, 1); glVertex2f(0, local_rect.h);
    glEnd();

}

