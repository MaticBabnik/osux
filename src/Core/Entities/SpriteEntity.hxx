#pragma once

#include "../../include.hxx"
#include "../Engine.hxx"

namespace Core::Entities {

    class SpriteEntity : public Entity {
    public:
        SpriteEntity(SDL_Texture *texture, SDL_Point origin, int w = -1, int h = -1, bool centered = true);

        SDL_Point getOrigin();

        void setOrigin(SDL_Point origin);

        void setSize(int x);

        void setSize(int x, int y);

        SDL_Rect getSize();


        void Render() override;

    protected:
        SDL_Rect rect;
        SDL_Point origin;
        SDL_Texture *texture;
        bool centered;
    };
}