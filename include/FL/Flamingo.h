
#ifndef FLAMINGO_H_
#define FLAMINGO_H_ 

#include <vector>

#include "SDL/SDL.h"
#include <OpenGL/gl.h>

#include "FL/Entity/EntityManager.h"
#include "FL/Components/FLComponents.h"


class Flamingo {

    private:
        bool _running;

    protected:
        EntityManager *_entityManager;

        SDL_Surface *_display;
        SDL_Rect _displaySize;
        std::vector<ScreenComp *> _screens;
        std::vector<SpriteComp *> _renderables;

    public:
        Flamingo();
        ~Flamingo();

        int Execute(int argc, char *argv[]);

        virtual int Init(int argc, char *argv[]) { return 0; };
        virtual void PreStep() {};
        virtual void PostStep() {};
        virtual void Cleanup() {};

        //void PushScreen(Screen &screen);
        //void RemoveScreen(Screen &screen);

    private:
        int _Init(int argc, char *argv[]);
        int _HandleEvents();
        void _Step();
        void _Render();
        void _Cleanup();

};

#endif

