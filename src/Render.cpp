
#include <iostream>
#include <list>

#include "FL/Flamingo.h"

void Flamingo::_Render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::list<Screen>::const_iterator iterator;
    Screen s;
    for (iterator = _screens.begin(); iterator != _screens.end(); ++iterator) {

        s = *iterator;

        glViewport(s.local_rect.x, s.local_rect.y, s.local_rect.w, s.local_rect.h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, s.local_rect.w, 0, s.local_rect.h, 1, -1);
        glMatrixMode(GL_MODELVIEW);

        s.Draw();
    }

    SDL_GL_SwapBuffers();

}

