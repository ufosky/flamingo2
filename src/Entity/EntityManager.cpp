#include "FL/Entity/EntityManager.h"


#include <iostream>

typedef std::map<Entity *, std::map<ComponentType, Component *> >::iterator EntityIterator;
typedef std::map<ComponentType, Component *>::iterator ComponentIterator;
typedef std::vector<ComponentType>::const_iterator DependencyIterator;


EntityManager::EntityManager() {

    _nextID = 0;
    _components = std::map<Entity *, std::map<ComponentType, Component *> >();
    _processed = std::set<ComponentType>();
	_registeredComponentVectors = std::map<ComponentType, std::vector<Component *> *>();
}

EntityManager::~EntityManager() {

	_DestroyEntities();

	_processed.clear();
	_registeredComponentVectors.clear();
}
		
void EntityManager::_DestroyEntities() {

	for (EntityIterator i = _components.begin(); i != _components.end(); i++) {
        delete i->first;
   
        for (ComponentIterator j = i->second.begin(); j != i->second.end(); j++) {
			_RemoveComponentFromRegisteredVector(j->first, j->second);
            delete j->second;
        }

		i->second.clear();
    }
	_components.clear();
}

void EntityManager::_DestroyComponents(Entity *e) {

	for (ComponentIterator i = _components[e].begin(); i != _components[e].end(); i++) {

		_RemoveComponentFromRegisteredVector(i->first, i->second);
		delete i->second;
	}
	_components[e].clear();
}

void EntityManager::_DestroyComponent(Entity *e, ComponentType type) {

	_RemoveComponentFromRegisteredVector(type, _components[e][type]);
	delete _components[e][type];
	_components[e].erase(type);

}

// Search in a registered vector for a component (must do this during removal of a component)
// Assumes vector elements have strictly increasing _ids. 
int EntityManager::_RegisteredComponentVectorSearch(std::vector<Component *> *v, Component *comp) {
	
	int s = 0, e = v->size(), m;
	while (e >= s) {
    	m = (s + e) / 2;
 
     	if ((*v)[m]->_id < comp->_id) {
        	s = m + 1;
      	} else if ((*v)[m]->_id > comp->_id) {
        	e = m - 1;
      	} else {
        	return m;
		}
  }
  return -1;
}

void EntityManager::_RemoveComponentFromRegisteredVector(ComponentType type, Component *comp) {
	if (_registeredComponentVectors.count(type)) {

		std::vector<Component *> *v = _registeredComponentVectors[type];
		int i = _RegisteredComponentVectorSearch(v, comp);
		v->erase(v->begin() + i);
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

	_DestroyComponents(e);
    delete e;
}

void EntityManager::AddComponent(Entity *e, Component *comp) {

    _components[e].insert(std::pair<ComponentType, Component *>(comp->_type, comp));
    comp->_id = ++_nextID;
    comp->_e = e;
	
	if (_registeredComponentVectors.count(comp->_type)) {
		_registeredComponentVectors[comp->_type]->push_back(comp);
	}
}

void EntityManager::RemoveComponent(Entity *e, ComponentType type) {

	_DestroyComponent(e, type);
}

void EntityManager::RemoveComponent(Entity *e, Component *comp) {

    EntityManager::RemoveComponent(e, comp->_type);
}

Component *EntityManager::GetComponent(Entity *e, ComponentType type) {

    return _components[e][type];
}

void EntityManager::RegisterComponentVector(ComponentType type, std::vector<Component *> *vect) {
	_registeredComponentVectors[type] = vect;
}

void EntityManager::UnregisterComponentVector(ComponentType type) {
	_registeredComponentVectors.erase(type);
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

