
#include <iostream>
#include <vector>

#include "FL/Flamingo.h"
#include <OpenGL/gl.h>

void Flamingo::_Render() {

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //
    //std::vector<ScreenComp *>::const_iterator i;
    //std::vector<SpriteComp *>::const_iterator j;
    //ScreenComp *s;
    //for (i = _screens.begin(); i != _screens.end(); ++i) {
	//	
    //    s = *i;

    //    glViewport(s->local_rect.x, s->local_rect.y, s->local_rect.w, s->local_rect.h);
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    glOrtho(0, s->local_rect.w, 0, s->local_rect.h, 1, -1);
    //    glMatrixMode(GL_MODELVIEW);

    //    glDisable(GL_TEXTURE_2D);

    //    s->PreDraw();
    //    
    //    glEnable(GL_TEXTURE_2D);
    //    
    //    for (j = _renderables.begin(); j != _renderables.end(); j++) {
    //        s->Draw(*j);
    //    }
    //    
    //    glDisable(GL_TEXTURE_2D);

    //    s->PostDraw();
    //}
    //
    //SDL_GL_SwapBuffers();
    
    screenSystem->Process();

}

