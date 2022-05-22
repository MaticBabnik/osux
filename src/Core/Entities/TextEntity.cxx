#include "TextEntity.hxx"

namespace Core::Entities {
    TextEntity::TextEntity(TTF_Font *font, SDL_Point origin, SDL_Color color, std::string text, bool centered) {

        this->origin = origin;

        this->font = font;
        this->color = color;
        this->text = text;
        this->repaintNeeded = true;

        this->centered = centered;

        this->textTexture = nullptr; //thank you CLion, very cool
        this->textSurface = nullptr;
    }

    void TextEntity::repaint() {
        SDL_FreeSurface(this->textSurface);
        SDL_DestroyTexture(this->textTexture); //free previous shit

        textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
        textTexture = SDL_CreateTextureFromSurface(Core::Engine::getRenderer(), textSurface);

        SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
        if (centered) {
            this->textRect.x = this->origin.x - this->textRect.w / 2;
            this->textRect.y = this->origin.y - this->textRect.h / 2;
        } else {
            this->textRect.x = this->origin.x;
            this->textRect.y = this->origin.y;
        }
    }

    void TextEntity::Render() {
        if (repaintNeeded) {
            repaint();
            repaintNeeded = false;
        }

        SDL_RenderCopy(Core::Engine::getRenderer(), this->textTexture, nullptr, &this->textRect);
    }

    TextEntity::~TextEntity() {
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    SDL_Point TextEntity::getOrigin() {
        return origin;
    }

    SDL_Color TextEntity::getColor() {
        return this->color;
    }

    string TextEntity::getText() {
        return this->text;
    }

    void TextEntity::setOrigin(SDL_Point origin) {
        this->origin = origin;
    }

    void TextEntity::setColor(SDL_Color color) {
        this->color = color;
        this->repaintNeeded = true;
    }

    void TextEntity::setText(string text) {
        this->text = text;
        this->repaintNeeded = true;
    }

    SDL_Rect TextEntity::getRect() {
        return textRect;
    }

    void TextEntity::forceRender() {
        repaint();
    }

}