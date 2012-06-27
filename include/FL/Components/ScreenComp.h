
#ifndef SCREENCOMP_H_
#define SCREENCOMP_H_ 

class ScreenComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FlComponents.h"

#include <SDL/SDL.h>

class ScreenComp : public Component {
	public:
		ScreenComp();
        ScreenComp(SDL_Rect *local);
		~ScreenComp();
        
		SDL_Rect local_rect;

		void Init();
		void Process();
		void Cleanup();

        void PreDraw();
		void Draw(RenderableComp *comp);
        void PostDraw();

	protected:
		void _SetType() {
            _type = FL_COMPTYPE_SCREEN;
            std::vector<ComponentType> _dependencies(1);
            _dependencies[0] = FL_COMPTYPE_POSITION;
        };

		void _LoadIdentity();
};

#endif

