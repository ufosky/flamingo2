
#ifndef FLAMINGO_H_
#define FLAMINGO_H_ 

#include <vector>
#include <string>

#include "SDL.h"
#include <OpenGL/gl.h>

#include "FL/Event/EventManager.h"
#include "FL/Event/FLEvents.h"

#include "FL/Entity/EntityManager.h"
#include "FL/Components/FLComponents.h"

#include "FL/Systems/ScreenSystem.h"


class Flamingo {

    private:
        bool _running;

    protected:
        EventManager *_eventManager;
        EntityManager *_entityManager;

        SDL_Surface *_display;
        SDL_Rect _displaySize;
        ScreenSystem *screenSystem;

    public:
        Flamingo();
        ~Flamingo();

        int Execute(int argc, char *argv[]);

        virtual int Init(int argc, char *argv[]) { return 0; };
        virtual void PreStep() {};
        virtual void PostStep() {};
        virtual void Cleanup() {};
        
        void MountDirectory(std::string path, std::string mtpt, int pre);

    private:
        int _Init(int argc, char *argv[]);
        int _HandleEvents();
        void _Step();
        void _Render();
        void _Cleanup();

};

#endif

