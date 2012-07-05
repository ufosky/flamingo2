
#include "FL/Entity/EntityManager.h"
#include "FL/Components/FLComponents.h"
#include "FL/Event/FLEvents.h"


std::vector<Component *> EntityManager::EmptyList;

EntityManager::EntityManager(EventManager *eventManager) {

    _nextID = 0;
    _eventManager = eventManager;
    _components.resize(FL_COMPTYPE_COUNT + 1);
}

EntityManager::~EntityManager() {

    for (std::vector<Entity *>::iterator it = _entities.begin(); it != _entities.end(); it++) {
        if (*it) {
            RemoveAllComponents(*it);
        }
    }

    _entities.clear();

    for (int i = 0; i < _components.size(); i++) {
        _components[i].clear();
    }

    _components.clear();
}

Entity *EntityManager::CreateEntity() {

    Entity *e = new Entity(++_nextID);
    if (_removedIndices.size()) {

        e->_index = _removedIndices.back();
        _removedIndices.pop_back();
        if (e->_index >= _entities.size()) {
            _entities.resize(e->_index + 1, NULL);
        }

        _entities[e->_index] = e;
    
    } else {
        e->_index = _entities.size();
        _entities.push_back(e);
    }

    _eventManager->FireEvent(EntityEvent(FL_EVENT_ENTITY_CREATE, e));
    return e;
}

void EntityManager::DestroyEntity(Entity *e) {

    _removedIndices.push_back(e->_index);
    _entities[e->_index] = NULL;
    RemoveAllComponents(e);

    _eventManager->FireEvent(EntityEvent(FL_EVENT_ENTITY_DELETE, e));
    delete e;
}

void EntityManager::AddComponent(Entity *e, Component *comp) {
    if (_components.size() <= comp->_type) {
        _components.resize(comp->_type + 1);
    }
    std::vector<std::vector<Component *> > &entities = _components[comp->_type];

    if (e->_index >= entities.size()) {
        entities.resize(e->_index + 1);
    }

    std::vector<Component *> &components = entities[e->_index];
    components.push_back(comp);

    e->_types.insert(comp->_type);
    _eventManager->FireEvent(ComponentEvent(FL_EVENT_COMPONENT_ADD, e, comp->_type));
}

void EntityManager::RemoveComponent(Entity *e, Component *comp) {
    
    if (_components.size() <= comp->_type) {
        return;
    }
    std::vector<std::vector<Component *> > &entities = _components[comp->_type];

    if (e->_index >= entities.size()) {
        return;
    }

    std::vector<Component *> &components = entities[e->_index];
    for (std::vector<Component *>::iterator it = components.begin(); it != components.end(); it++) {
        if (*it == comp) {
            components.erase(it);
        }
    }

    if (components.size() == 0) {
        e->_types.erase(comp->_type);
    }

    _eventManager->FireEvent(ComponentEvent(FL_EVENT_COMPONENT_REMOVE, e, comp->_type));
}

void EntityManager::_RemoveAllComponents(Entity *e, ComponentType type) {
    //if (_components.size() <= type) {
    //    return;
    //}
    std::vector<std::vector<Component *> > &entities = _components[type];

    if (e->_index >= entities.size()) {
        return;
    }

    std::vector<Component *> &components = entities[e->_index];
    while (components.size()) {

        delete components.back();
        components.pop_back();

        _eventManager->FireEvent(ComponentEvent(FL_EVENT_COMPONENT_REMOVE, e, type));
    }

    components.clear();
}

void EntityManager::RemoveAllComponents(Entity *e) {

    for (std::set<ComponentType>::iterator it = e->_types.begin(); it != e->_types.end(); it++) {
        _RemoveAllComponents(e, *it);
    }
    e->_types.clear();
}

void EntityManager::RemoveAllComponents(Entity *e, ComponentType type) {
    _RemoveAllComponents(e, type);
    e->_types.erase(type);
}

const std::vector<Component *> &EntityManager::GetComponents(Entity *e, ComponentType type) {
    if (_components.size() <= type) {
        return EmptyList;
    }
    std::vector<std::vector<Component *> > &entities = _components[type];

    if (e->_index >= entities.size()) {
        return EmptyList;
    }

    return entities[e->_index];
}

Component *EntityManager::GetComponent(Entity *e, ComponentType type) {
    if (_components.size() <= type) {
        return NULL;
    }
    std::vector<std::vector<Component *> > &entities = _components[type];

    if (e->_index >= entities.size()) {
        return NULL;
    }

    return entities[e->_index][0];
}

