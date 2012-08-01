
#include "FL/Systems/ScreenSystem.h"
#include "FL/Components/FLComponents.h"
#include "FL/Events/InputEvent.h"

#include <Python.h>

#include <OpenGL/gl.h>
#include "SDL.h"

ScreenSystem::ScreenSystem(EventManager *eventManager, EntityManager *entityManager) : EntitySystem(eventManager, entityManager) {

    _types.insert(FL_COMPTYPE_SCREEN);
}

ScreenSystem::~ScreenSystem() {

    _sprites.clear();
}

bool ScreenSystem::HandleComponentAdd(Entity *e, ComponentType type) {
    if (type == FL_COMPTYPE_SPRITE) {
        _sprites.insert(e);
        return true;
    }
    return false;
}

bool ScreenSystem::HandleComponentRemove(Entity *e, ComponentType type) {
    if (type == FL_COMPTYPE_SPRITE) {
        _sprites.erase(e);
        return true;
    }
    return false;
}

bool ScreenSystem::ShouldProcess() {
    return true;
}

void ScreenSystem::Begin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void background(ScreenComp *s) {
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex2f(0, 0);
        glColor3f(1, 1, 0); glVertex2f(s->local_rect.w, 0);
        glColor3f(1, 0, 1); glVertex2f(s->local_rect.w, s->local_rect.h);
        glColor3f(1, 1, 1); glVertex2f(0, s->local_rect.h);
    glEnd();
    
    glEnable(GL_TEXTURE_2D);
}

void ScreenSystem::ProcessEntity(Entity *e) {

    ScreenComp *s = (ScreenComp *)e->GetAs(FL_COMPTYPE_SCREEN);
    if (s == NULL) {
        return;
    }

    glViewport(s->local_rect.x, s->local_rect.y, s->local_rect.w, s->local_rect.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, s->local_rect.w, 0, s->local_rect.h, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    background(s);

    // Draw Sprites
    
    SpriteComp *spr;
    PositionComp *pos;
    for (std::set<Entity *>::const_iterator it = _sprites.begin(); it != _sprites.end(); it++) {
        spr = (SpriteComp *)(*it)->GetAs(FL_COMPTYPE_SPRITE);
        pos = (PositionComp *)(*it)->GetAs(FL_COMPTYPE_POSITION);

        glTranslatef(512, 384, 0);
        glTranslatef(pos->GetX(), pos->GetY(), 0);
        
        //// Test
        glBindTexture(GL_TEXTURE_2D, spr->img->img);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex2f(pos->GetCornerX(0), pos->GetCornerY(0));
            
            glTexCoord2f(1, 0);
            glVertex2f(pos->GetCornerX(1), pos->GetCornerY(1));
            
            glTexCoord2f(1, 1);
            glVertex2f(pos->GetCornerX(2), pos->GetCornerY(2));
            
            glTexCoord2f(0, 1);
            glVertex2f(pos->GetCornerX(3), pos->GetCornerY(3));
        glEnd();
    }

    s->ProcessScript();
}

void ScreenSystem::End() {
    SDL_GL_SwapBuffers();
}

