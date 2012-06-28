
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

void ScreenComp::PreDraw() {
    _LoadIdentity();
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex2f(0, 0);
        glColor3f(1, 1, 0); glVertex2f(local_rect.w, 0);
        glColor3f(1, 0, 1); glVertex2f(local_rect.w, local_rect.h);
        glColor3f(1, 1, 1); glVertex2f(0, local_rect.h);
    glEnd();
}

void ScreenComp::Draw(SpriteComp *comp) {
    _LoadIdentity();

    PositionComp *pos = (PositionComp *)comp->entity->GetAs(FL_COMPTYPE_POSITION);
    //PositionComp *spos = (PositionComp *)entity->GetAs(FL_COMPTYPE_POSITION);

    //glColor3f(0, 0, 0);
    glTranslatef(512, 384, 0);
    glTranslatef(pos->pos[0], pos->pos[1], 0);
    
    // Test
    glBindTexture(GL_TEXTURE_2D, comp->img->img);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(pos->size(0,0), pos->size(1,0));
        glTexCoord2f(1, 0);
        glVertex2f(pos->size(0,1), pos->size(1,1));
        glTexCoord2f(1, 1);
        glVertex2f(pos->size(0,2), pos->size(1,2));
        glTexCoord2f(0, 1);
        glVertex2f(pos->size(0,3), pos->size(1,3));
    glEnd();
}

void ScreenComp::PostDraw() {

}

void ScreenComp::_LoadIdentity() {
    glLoadIdentity();
}

