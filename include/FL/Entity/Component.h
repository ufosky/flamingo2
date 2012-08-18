
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

#include <sqlite3.h>

class Component {

    friend class EntityManager;

    public:
        Component(ComponentType type) : script(NULL), _type(type) {};
        Component(ComponentType type, std::string file, std::string module) : script(NULL), _type(type) {
            LoadScript(file, module);
        }
        virtual ~Component();
        
        Entity *entity;

        ComponentID GetID() { return _id; };
        ComponentType GetType() { return _type; };

        bool LoadScript(std::string file, std::string module);
        void ProcessScript();
        std::string scriptname;
        PyObject *script;

        int Dump(sqlite3 *db);
        int Load(sqlite3 *db);

    protected:
        ComponentType _type;
        ComponentID _id;

        virtual char *Columns();
        virtual char *DumpRow();
};

class ComponentEvent : public EventData {
    public:
        ComponentEvent(EventType _type, Entity *_e, ComponentType _ctype) : EventData(_type), e(_e), ctype(_ctype) {};
        Entity *e;
        ComponentType ctype;
};

#endif

