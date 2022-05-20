#include "SpriteEntity.hxx"

Core::Entities::SpriteEntity::SpriteEntity(SDL_Texture *texture, SDL_Point origin, int w, int h, bool centered) {
    this->texture = texture;
    this->origin = origin;
    this->centered = centered;
    if (w == -1 || h == -1)
        SDL_QueryTexture(this->texture,
                         nullptr, nullptr,
                         &this->rect.w, &this->rect.h);

    if (w != -1) this->rect.w = w;
    if (h != -1) this->rect.h = h;

    if (!this->centered) {
        this->rect.x = this->origin.x;
        this->rect.y = this->origin.y;
    } else {
        this->rect.x = this->origin.x - this->rect.w / 2;
        this->rect.y = this->origin.y - this->rect.h / 2;
    }
}

SDL_Point Core::Entities::SpriteEntity::getOrigin() {
    return this->origin;
}

void Core::Entities::SpriteEntity::setOrigin(SDL_Point origin) {
    this->origin = origin;
}

void Core::Entities::SpriteEntity::setSize(int x) {
    this->rect.w = this->rect.h = x;

    if (!this->centered) {
        this->rect.x = this->origin.x;
        this->rect.y = this->origin.y;
    } else {
        this->rect.x = this->origin.x - this->rect.w / 2;
        this->rect.y = this->origin.y - this->rect.h / 2;
    }
}

void Core::Entities::SpriteEntity::setSize(int x, int y) {
    this->rect.w = x;
    this->rect.h = y;

    if (!this->centered) {
        this->rect.x = this->origin.x;
        this->rect.y = this->origin.y;
    } else {
        this->rect.x = this->origin.x - this->rect.w / 2;
        this->rect.y = this->origin.y - this->rect.h / 2;
    }
}

SDL_Rect Core::Entities::SpriteEntity::getSize() {
    return this->rect;
}

void Core::Entities::SpriteEntity::Render() {
    auto r = Engine::getRenderer();
    SDL_RenderCopy(r, this->texture, nullptr, &this->rect);
}
