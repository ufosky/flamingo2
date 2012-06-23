
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "FL/Entity/Entity.h"
#include <vector>

typedef unsigned int ComponentType;
typedef unsigned int ComponentID;

class Component {

    friend class EntityManager;

    public:
        virtual ~Component();

        virtual void Init();
        virtual void Cleanup();
        virtual void Process();

    private:
        ComponentType _type;
        unsigned int _bit;
        std::vector<ComponentType> _dependencies;

        Entity *_e;
};

#endif

