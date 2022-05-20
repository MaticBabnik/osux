#pragma once
#include "../../include.hxx"

#include "../Engine.hxx"
#include "../Entity.hxx"

namespace Core::Entities {
    class RectEntity : public Core::Entity {
    public:
        RectEntity(SDL_Rect r, SDL_Color c);
        void Render() override;
    protected:
        SDL_Rect rect;
        SDL_Color color;
    };
}