
#ifndef _INPUTCOMP_H_
#define _INPUTCOMP_H_ 

class InputComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FlComponents.h"


class InputComp : public Component {
	public:
		InputComp() : Component(FL_COMPTYPE_INPUT) {};
		~InputComp();
};

#endif
 
