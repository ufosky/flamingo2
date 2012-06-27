
#ifndef SCREENCOMP_H_
#define SCREENCOMP_H_ 

#include "FL/Entity/Component.h"
#include "FL/Components/FlComponents.h"

#include <SDL/SDL.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class ScreenComp : public Component {
	public:
		ScreenComp();
        ScreenComp(SDL_Rect *local);
		~ScreenComp();
        
		SDL_Rect local_rect;

		void Init();
		void Process();
		void Cleanup();

		void Draw();

	protected:
		void _SetType() { _type = FL_COMPTYPE_SCREEN; };

		void _LoadIdentity();
};

#endif

