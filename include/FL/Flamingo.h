
#ifndef FLAMINGO_H_
#define FLAMINGO_H_ 

#include <list>

#include <SDL/SDL.h>
#include <OpenGL/gl.h>


#include "FL/Entity/EntityManager.h"
#include "FL/Screen.h"

class Flamingo {

    private:
        bool _running;

    protected:
        EntityManager *_entityManager;

        SDL_Surface *_display;
        SDL_Rect _displaySize;
        std::list<Screen> _screens;

    public:
        Flamingo();
        ~Flamingo();

        int Execute();

        virtual int Init() { return 0; };
        virtual void PreStep() {};
        virtual void PostStep() {};
        virtual void Cleanup() {};

        void PushScreen(Screen &screen);
        void RemoveScreen(Screen &screen);

    private:
        int _Init();
        int _HandleEvents();
        void _Step();
        void _Render();
        void _Cleanup();

};

#endif

