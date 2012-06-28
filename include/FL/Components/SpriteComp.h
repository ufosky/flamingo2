
#ifndef SPRITECOMP_H_
#define SPRITECOMP_H_

class SpriteComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FlComponents.h"

#include <OpenGL/gl.h>

#include <string>

class SpriteComp : public Component {
	public:
		SpriteComp();
        SpriteComp(std::string file);
		~SpriteComp();

        void LoadImage(std::string file);

		void Process();
        
        GLuint img;

	protected:
		void _SetType() {
            _type = FL_COMPTYPE_SPRITE;
        };

        void _LoadImage(std::string file);

};

#endif

