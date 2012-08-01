
%module inputevent
%{
#include "FL/Events/InputEvent.h"
%}

class InputEvent : public EventData {
    public:
        InputEvent(int _inputtype, int _inputkey);
        int inputType, inputKey;
};

