
#include "FL/Entity/EntityManager.h"
#include "FL/Components/FLComponentDefines.h"
#include "FL/Events/FLEvents.h"


std::vector<Component *> EntityManager::EmptyList;

EntityManager::EntityManager(EventManager *eventManager) {

    _nextID = 0;
    _eventManager = eventManager;
    _components.resize(FL_COMPTYPE_COUNT + 1);

    factory = new ComponentFactory();
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
    delete factory;
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

    _eventManager->FireEvent(new EntityEvent(FL_EVENT_ENTITY_CREATE, e));
    e->_entityManager = this;
    return e;
}

void EntityManager::DestroyEntity(Entity *e) {

    _removedIndices.push_back(e->_index);
    _entities[e->_index] = NULL;
    RemoveAllComponents(e);

    _eventManager->FireEvent(new EntityEvent(FL_EVENT_ENTITY_DELETE, e));
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

    comp->_id = ++_nextID;
    comp->entity = e;

    std::vector<Component *> &components = entities[e->_index];
    components.push_back(comp);

    e->_types.insert(comp->_type);
    _eventManager->FireEvent(new ComponentEvent(FL_EVENT_COMPONENT_ADD, e, comp->_type));
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

    comp->entity = NULL;

    _eventManager->FireEvent(new ComponentEvent(FL_EVENT_COMPONENT_REMOVE, e, comp->_type));
}

void EntityManager::_RemoveAllComponents(Entity *e, ComponentType type) {
    std::vector<std::vector<Component *> > &entities = _components[type];

    if (e->_index >= entities.size()) {
        return;
    }

    std::vector<Component *> &components = entities[e->_index];
    while (components.size()) {
        
        components.pop_back();
        _eventManager->FireEvent(new ComponentEvent(FL_EVENT_COMPONENT_REMOVE, e, type));
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

    if (!entities[e->_index].size()) {
        return NULL;
    }

    return entities[e->_index][0];
}

#include <iostream>

int EntityManager::Dump(std::string filename) {
    sqlite3 *db;
    std::string f = std::string(PHYSFS_getBaseDir()) + filename;
    std::cout << "Loading DB: " << f << "\n";
    int rc = sqlite3_open(f.c_str(), &db);
    char *msg, *query;

    if (rc) {
        return rc;
    }

    rc = sqlite3_exec(db, "create table if not exists tblEntities(entityID int PRIMARY KEY);"
            "create table if not exists tblEntityComponents(entityID int, componentType int, componentID int PRIMARY KEY)", NULL, NULL, &msg);
    if (!rc) {
        std::vector<Entity *>::iterator entityit;
        for (entityit = _entities.begin(); entityit != _entities.end(); entityit++) {
            Entity *e = *entityit;
            
            if (e == NULL) {
                continue;
            }

            // Insert EntityID
            query = sqlite3_mprintf("insert into tblEntities (entityID) values (%d)", e->_id);
            rc = sqlite3_exec(db, query, NULL, NULL, &msg);
            if (rc) {
                return rc;
            }
            
            std::set<ComponentType>::iterator typeit;
            //std::cout << "Entity: " << e->_id << "\n";

            for (typeit = e->_types.begin(); typeit != e->_types.end(); typeit++) {
                ComponentType type = *typeit;
            
                const std::vector<Component *> components = GetComponents(e, type);
                std::vector<Component *>::const_iterator compit;
                for (compit = components.begin(); compit != components.end(); compit++) {
                    
                    // Insert Component into tblEntityComponents
                    query = sqlite3_mprintf("insert into tblEntityComponents values (%d, %d, %d)", e->_id, type, (*compit)->_id);
                    rc = sqlite3_exec(db, query, NULL, NULL, &msg);
                    if (rc) {
                        return rc;
                    }

                    rc = (*compit)->Dump(db);
                    if (rc) {
                        return rc;
                    }
                }
            }
        }
    } 

    sqlite3_close(db);
    return rc;
}

int EntityManager::Load(std::string filename) {
    return 0;
}

