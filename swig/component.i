
%module component
%{
#include "FL/Entity/Entity.h"
#include "FL/Entity/Component.h"
#include <string>
%}

%include "include/FL/Components/FLComponentDefines.h"

typedef unsigned int EntityID;
typedef unsigned int ComponentType;
typedef unsigned int ComponentID;

class Entity {
    public:
        Entity(EntityID id) : _id(id) {};
        ~Entity();

        bool HasComponentType(ComponentType type);

    protected:
        EntityID _id;
        unsigned int _index;
        std::set<ComponentType> _types;
        EntityManager *_entityManager;
};

class Component {

    public:
        Component(ComponentType type) : _type(type) {};
        virtual ~Component() {};

        bool LoadScript(std::string file, std::string module);

        Entity *entity;

    protected:
        ComponentType _type;
        ComponentID _id;
        std::string _script;
};

