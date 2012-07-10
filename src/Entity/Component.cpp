
#include "FL/Entity/Component.h"

Component::~Component() {

}

bool Component::LoadScript(std::string scr) {

    script = scr;
    return true;
}

void Component::ProcessScript(ComponentType comptype) {

}

