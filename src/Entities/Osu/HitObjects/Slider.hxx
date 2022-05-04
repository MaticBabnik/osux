
#pragma once

#include "SDL2/SDL.h"

#include "../../../Core/Engine.hxx"
#include "../../../IO/Beatmap.hxx"
#include "../../../Util/Osu.hxx"
#include "../PlayingFieldEntity.hxx"
#include <cmath>

#define APPROACH_Slider_SIZE_MUL 7.0

namespace Osu {

    class Slider : public Core::Entity {
    protected:
        PlayingFieldEntity *parent;
        SDL_Rect rect;
        int x, y, time;

    public:
        Slider(IO::HitObject *hitObject, IO::Beatmap *beatmap, PlayingFieldEntity *playingFieldEntity) {
            //setup the draw area
            this->parent = playingFieldEntity;
            this->x = hitObject->x;
            this->y = hitObject->y;
            this->time = hitObject->time;

            auto s = 32;

            this->rect.w = this->rect.h = s;
            auto pr = parent->getField();

            this->rect.x = this->x - s / 2 + pr.x;
            this->rect.y = this->y - s / 2 + pr.y;

            logher(ERROR, "Slider") << "Sliders aren't implemented yet" << endlog;
        }

        void Render() override {
            auto t = parent->getTime();

            if (time + 2000 < t) {
                this->parent->DestroyEntity(this);
                return;
            }
            auto r = Core::Engine::getRenderer();

            SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("intro_1"),
                           nullptr, &rect);

        }

    };
}


