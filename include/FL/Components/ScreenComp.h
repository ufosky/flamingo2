
#ifndef SCREENCOMP_H_
#define SCREENCOMP_H_ 

class ScreenComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FLComponents.h"

#include "SDL.h"


class ScreenComp : public Component {
	public:
		ScreenComp();
        ScreenComp(SDL_Rect *local);
		~ScreenComp();
		
        SDL_Rect local_rect;
    
    private:
        virtual char *Columns();
        virtual char *DumpRow();
};

#endif

