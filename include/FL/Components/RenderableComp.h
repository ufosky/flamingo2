
#ifndef RENDERABLECOMP_H_
#define RENDERABLECOMP_H_

class RenderableComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FlComponents.h"

class RenderableComp : public Component {
	public:
		RenderableComp();
		~RenderableComp();

		void Process();

	protected:
		void _SetType() {
            _type = FL_COMPTYPE_RENDERABLE;
            std::vector<ComponentType> _dependencies(1);
            _dependencies[0] = FL_COMPTYPE_POSITION;
        };
};

#endif

