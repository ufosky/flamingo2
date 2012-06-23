
#include "FL/Entity/Entity.h"

Entity::Entity(EntityID id) {
    _id = id;
}

Entity::~Entity() {

};

bool Entity::HasComponentType(ComponentType type) {
    return _components.find(type) != _components.end();
}

Component *Entity::GetAs(ComponentType type) {
    return _entityManager->GetComponent(this, type);
}

