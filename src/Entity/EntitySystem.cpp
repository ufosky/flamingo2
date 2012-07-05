
#include "FL/Entity/EntitySystem.h"

EntitySystem::EntitySystem(EventManager *eventManager, EntityManager *entityManager) {

    _eventManager = eventManager;
    _entityManager = entityManager;

    _eventManager->AddListener(this, FL_EVENT_COMPONENT_ADD);
    _eventManager->AddListener(this, FL_EVENT_COMPONENT_REMOVE);

}

EntitySystem::~EntitySystem() {

    _eventManager->RemoveListener(this, FL_EVENT_COMPONENT_ADD);
    _eventManager->RemoveListener(this, FL_EVENT_COMPONENT_REMOVE);
    _active.clear();
}

void EntitySystem::Process() {

    if (ShouldProcess()) {
        Begin();
        for (std::set<Entity *>::iterator it = _active.begin(); it != _active.end(); it++) {
            ProcessEntity(*it);
        }
        End();
    }
}

bool EntitySystem::HandleEvent(EventData const &event) {
    
    const ComponentEvent &data = static_cast<const ComponentEvent&>(event);
    
    switch(event.type) {
        case FL_EVENT_COMPONENT_ADD:
            
            if (!HandleComponentAdd(data.e, data.ctype)) {
            
                if (data.e->HasComponentTypes(_types)) {
                    _active.insert(data.e);
                }
            }
            break;

        case FL_EVENT_COMPONENT_REMOVE:

            if (!HandleComponentRemove(data.e, data.ctype)) {
                _active.erase(data.e);
            }
            break;
    }
    return false;
}

