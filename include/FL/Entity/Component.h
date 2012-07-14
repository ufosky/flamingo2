
#ifndef COMPONENT_H_
#define COMPONENT_H_

class Component;
typedef unsigned int ComponentType;
typedef unsigned int ComponentID;

#include "FL/Entity/Entity.h"
#include "FL/Event/Event.h"

#include <Python.h>
#include <vector>
#include <string>

class Component {

    friend class EntityManager;

    public:
        Component(ComponentType type) : script(NULL), _type(type) {};
        virtual ~Component();

        bool LoadScript(std::string file, std::string module);
        void ProcessScript();
        std::string scriptname;
        PyObject *script;

        Entity *entity;

        ComponentID GetID() { return _id; };
        ComponentType GetType() { return _type; };

    protected:
        ComponentType _type;
        ComponentID _id;
};

class ComponentEvent : public EventData {
    public:
        ComponentEvent(EventType _type, Entity *_e, ComponentType _ctype) : EventData(_type), e(_e), ctype(_ctype) {};
        Entity *e;
        ComponentType ctype;
};

#endif

