
#include "FL/Entity/Entity.h"

#include <iostream>

Entity::~Entity() {
    _types.clear();
};

bool Entity::HasComponentType(ComponentType type) {
    return _types.find(type) != _types.end();
}

bool Entity::HasComponentTypes(std::set<ComponentType> types) {

    for (std::set<ComponentType>::const_iterator it = types.begin(); it != types.end(); it++) {

        if (!HasComponentType(*it)) {
            return false;
        }
    }
    return true;
}

