#pragma once

#include "../../include.hxx"
#include "../Engine.hxx"

namespace Core::Entities {

    class TextEntity : public Entity {
    public:
        TextEntity(TTF_Font *font, SDL_Point origin, SDL_Color color, std::string text,bool centered = true);

        virtual SDL_Point getOrigin();

        virtual void setOrigin(SDL_Point origin);

        virtual SDL_Color getColor();

        virtual void setColor(SDL_Color color);

        virtual string getText();

        virtual void setText(string text);

        virtual SDL_Rect getRect() override;

        virtual void forceRender();

        ~TextEntity() override;

        void Render() override;

    protected:
        string text;
        SDL_Rect textRect;
        SDL_Point origin;
        SDL_Color color;
        TTF_Font *font;
        SDL_Surface *textSurface;
        SDL_Texture *textTexture;
        bool centered;

        bool repaintNeeded;

        void repaint();
    };
}