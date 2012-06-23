
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class Component;
typedef unsigned int ComponentType;
typedef unsigned int ComponentID;

#include "FL/Entity/Entity.h"
#include <vector>

class Component {

    friend class EntityManager;

    public:
        Component() {};
        virtual ~Component() {};

        virtual void Init() = 0;
        virtual void Cleanup() = 0;
        virtual void Process() = 0;

    protected:
        ComponentType _type;
        ComponentID _id;
        std::vector<ComponentType> _dependencies;

        Entity *_e;
};

#endif

