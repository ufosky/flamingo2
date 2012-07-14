
#ifndef SPRITECOMP_H_
#define SPRITECOMP_H_

class SpriteComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FLComponents.h"

#include "FL/Image.h"

#include <string>

class SpriteComp : public Component {
	public:
		SpriteComp();
        SpriteComp(Image *image);
		~SpriteComp();
		
        void LoadImage(std::string file);

        Image *img;
};

#endif

