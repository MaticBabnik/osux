#include "Entity.hxx"

namespace Core {
    void Entity::setParent(Entity *p) {
        this->parent = p;
    }

    Entity::~Entity() {
    }

    SDL_Rect Entity::getRect() {
        return {0,0,0,0};
    }
}