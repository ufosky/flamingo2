
#ifndef SPRITECOMP_H_
#define SPRITECOMP_H_

class SpriteComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FlComponents.h"

#include "FL/Image.h"

#include <string>

class SpriteComp : public Component {
	public:
		SpriteComp();
        SpriteComp(Image *image);
		~SpriteComp();
		
        void Process();

        void LoadImage(std::string file);

        Image *img;


	protected:
		void _SetType() {
            _type = FL_COMPTYPE_SPRITE;
        };

};

#endif

