
#ifndef FLAMINGO_H_
#define FLAMINGO_H_ 

#include <vector>
#include <string>

#include "SDL.h"
#include <OpenGL/gl.h>

#include "FL/Event/EventManager.h"
#include "FL/Event/FLEvents.h"

#include "FL/Entity/EntityManager.h"

#include "FL/Systems/FLSystems.h"

#include "FL/Time.h"

class Flamingo {

    private:
        bool _running;

    protected:
        EventManager *_eventManager;
        EntityManager *_entityManager;

        Clock *_masterClock;

        SDL_Surface *_display;
        SDL_Rect _displaySize;
        
        InputSystem *inputSystem;
        ScreenSystem *screenSystem;

        std::string pythonDir;

    public:
        Flamingo();
        ~Flamingo();

        int Execute(int argc, char *argv[]);

        virtual int Init(int argc, char *argv[]) { return 0; };
        virtual void PreStep() {};
        virtual void PostStep() {};
        virtual void Cleanup() {};

    private:
        int _Init(int argc, char *argv[]);
        int _HandleEvents();
        void _Step();
        void _Render();
        void _Cleanup();

};

#endif

