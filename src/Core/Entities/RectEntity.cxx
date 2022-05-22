//
// Created by babnik on 5/20/22.
//

#include "RectEntity.hxx"

Core::Entities::RectEntity::RectEntity(SDL_Rect r, SDL_Color c) {
    this->rect = r;
    this->color = c;
}

void Core::Entities::RectEntity::Render() {
    auto r = Engine::getRenderer();

    SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r,color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(r,&rect);
}
