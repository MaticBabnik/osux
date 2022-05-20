#pragma once
#include <SDL2/SDL.h> // SDL_Rect

namespace Core {

    class Entity {
    protected:
        Entity *parent;
    public:
        virtual void Render() = 0;

        virtual SDL_Rect getRect();

        virtual ~Entity() = 0;

        void setParent(Entity *p);
    };

}