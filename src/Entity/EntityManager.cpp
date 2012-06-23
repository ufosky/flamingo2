
#include "FL/Entity/EntityManager.h"

typedef std::map<Entity *, std::map<ComponentType, Component *> >::iterator EntityIterator;
typedef std::map<ComponentType, Component *>::iterator ComponentIterator;


EntityManager::EntityManager() {

    _nextID = 0;
    _components = std::map<Entity *, std::map<ComponentType, Component *> >();
}

EntityManager::~EntityManager() {

    for (EntityIterator i = _components.begin(); i != _components.end(); i++) {
        delete i->first;
   
        for (ComponentIterator j = i->second.begin(); j != i->second.end(); j++) {
            delete j->second;
        }
    }
}

Entity *EntityManager::CreateEntity() {

    Entity *e = new Entity(++_nextID);
    _components[e] = std::map<ComponentType, Component *>();
    e->_components = _components[e];
    e->_entityManager = this;
    return e;
}

void EntityManager::DestroyEntity(Entity *e) {
    
    std::map<ComponentType, Component *> comps = _components[e];
    for (ComponentIterator j = comps.begin(); j != comps.end(); j++) {
        delete j->second;
    }
    _components.erase(e);
    delete e;
}

void EntityManager::AddComponent(Entity *e, Component *comp) {

    _components[e].insert(std::pair<ComponentType, Component *>(comp->_type, comp));
    comp->_id = ++_nextID;
    comp->_e = e;
}

void EntityManager::RemoveComponent(Entity *e, ComponentType type) {

    _components[e].erase(type);
}

void EntityManager::RemoveComponent(Entity *e, Component *comp) {

    EntityManager::RemoveComponent(e, comp->_type);
}

Component *EntityManager::GetComponent(Entity *e, ComponentType type) {

    return _components[e][type];
}

void EntityManager::Process() {

}

