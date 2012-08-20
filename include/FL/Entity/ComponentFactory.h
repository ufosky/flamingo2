
#ifndef COMPONENTFACTORY_H_
#define COMPONENTFACTORY_H_

#include <map>
#include "FL/Entity/Component.h"

template<typename T> Component *createT() { return new T; };

class ComponentFactory {

    typedef std::map<ComponentType, Component *(*)()> regmap_type;

    public:
        ComponentFactory() {
            regmap = regmap_type();
        }

        Component *CreateInstance(ComponentType type) {

            regmap_type::iterator it = regmap.find(type);
            if (it == regmap.end()) {
                return NULL;
            }

            return it->second();
        }

        template<typename T>
        void RegisterComponent(ComponentType type) {
            regmap[type] = &createT<T>;
        }

        regmap_type regmap;
};

#endif

