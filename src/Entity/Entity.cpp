
#include "FL/Entity/Entity.h"
#include "FL/swigpyrun.h"

#include <iostream>

Entity::~Entity() {
    _types.clear();
    Py_XDECREF(pyEntity);
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

#include <vector>
Component *Entity::GetAs(ComponentType type) {

    return this->_entityManager->GetComponent(this, type);
}

void Entity::LoadPyEntity() {
    swig_type_info *t = SWIG_TypeQuery("Entity *");
    pyEntity = SWIG_NewPointerObj(this, t, SWIG_POINTER_OWN);
    Py_INCREF(pyEntity);
}

