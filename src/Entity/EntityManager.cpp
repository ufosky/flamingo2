
#include "FL/Entity/EntityManager.h"

typedef std::map<Entity *, std::map<ComponentType, Component *> >::iterator EntityIterator;
typedef std::map<ComponentType, Component *>::iterator ComponentIterator;
typedef std::vector<ComponentType>::const_iterator DependencyIterator;


EntityManager::EntityManager() {

    _nextID = 0;
    _components = std::map<Entity *, std::map<ComponentType, Component *> >();
    _processed = std::set<ComponentType>();
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

    for (EntityIterator i = _components.begin(); i != _components.end(); i++) {
        for (ComponentIterator j = i->second.begin(); j != i->second.end(); j++) {
            EntityManager::_Process(i->first, j->second);
        }
    }

    _processed.clear();

}

void EntityManager::_Process(Entity *e, Component *comp) {

    if (_processed.find(comp->_type) != _processed.end()) {
        return;
    }

    for (DependencyIterator i = comp->_dependencies.begin(); i != comp->_dependencies.end(); i++) {
        if (_processed.find(*i) == _processed.end()) {
            EntityManager::_Process(e, _components[e][*i]);
        }
    }

    comp->Process();
    _processed.insert(comp->_type);
}
