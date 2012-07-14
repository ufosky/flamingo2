
#ifndef INPUTCOMP_H_
#define INPUTCOMP_H_ 

class InputComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FLComponents.h"


class InputComp : public Component {
	public:
		InputComp() : Component(FL_COMPTYPE_INPUT) {};
		~InputComp();
};

#endif
 
