#pragma once

#include "../../include.hxx"
#include "../Engine.hxx"

namespace Core::Entities {

    class TextEntity : public Entity {
    public:
        TextEntity(TTF_Font *font, SDL_Point origin, SDL_Color color, std::string text);

        SDL_Point getOrigin();

        void setOrigin(SDL_Point origin);

        SDL_Color getColor();

        void setColor(SDL_Color color);

        string getText();

        void setText(string text);

        ~TextEntity() override;

        void Render() override;

    protected:
        string text;
        SDL_Rect textRect;
        SDL_Color color;
        TTF_Font *font;
        SDL_Surface *textSurface;
        SDL_Texture *textTexture;

        bool repaintNeeded;

        void repaint();
    };
}