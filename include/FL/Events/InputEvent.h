
#ifndef _INPUTEVENT_H_
#define _INPUTEVENT_H_

#include "FL/Event/Event.h"
#include "FL/Events/FLEvents.h"

class InputEvent : public EventData {
    public:
        InputEvent(int _inputType, int _inputKey) : EventData(FL_EVENT_INPUT), inputType(_inputType), inputKey(_inputKey) {};
        int inputType, inputKey;
};

#endif

