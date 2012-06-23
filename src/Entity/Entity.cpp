
#include "FL/Entity/Entity.h"


Entity::~Entity() {

};

bool Entity::HasComponentType(ComponentType type) {
    return false;
}

Component *Entity::GetAs(ComponentType type) {
    return NULL;
}

