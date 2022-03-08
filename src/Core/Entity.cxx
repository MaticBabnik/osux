#include "Entity.hxx"

namespace Core {
    void Entity::setParent(Entity *p) {
        this->parent = p;
    }

    Entity::~Entity() {
    }
}