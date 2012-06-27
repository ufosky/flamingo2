
#include <iostream>
#include <vector>

#include "FL/Flamingo.h"
#include <OpenGL/gl.h>

void Flamingo::_Render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<ScreenComp *>::const_iterator i;
    std::vector<RenderableComp *>::const_iterator j;
    ScreenComp *s;
    for (i = _screens.begin(); i != _screens.end(); ++i) {
		
        s = *i;

        glViewport(s->local_rect.x, s->local_rect.y, s->local_rect.w, s->local_rect.h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, s->local_rect.w, 0, s->local_rect.h, 1, -1);
        glMatrixMode(GL_MODELVIEW);

        s->PreDraw();
        
        for (j = _renderables.begin(); j != _renderables.end(); j++) {
            s->Draw(*j);
        }

        s->PostDraw();
    }

    SDL_GL_SwapBuffers();

}

