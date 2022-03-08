
#pragma once

#include "SDL2/SDL.h"

#include "../../../Core/Engine.hxx"
#include "../../../IO/Beatmap.hxx"
#include "../../../Util/Osu.hxx"
#include "../PlayingFieldEntity.hxx"
#include <cmath>

#define APPROACH_CIRCLE_SIZE_MUL 7.0

namespace Osu {

    class Circle : public Core::Entity {
    protected:
        PlayingFieldEntity *parent;
        SDL_Rect rect;

        SDL_Rect approach_rect;
        int a_start_size, size;

        int x, y, time;
        int startTime;

    public:
        Circle(IO::HitObject *hitObject, IO::Beatmap *beatmap, PlayingFieldEntity *playingFieldEntity) {
            //setup the draw area
            this->parent = playingFieldEntity;
            this->x = hitObject->x;
            this->y = hitObject->y;
            this->time = hitObject->time;

            this->startTime = parent->getTime();

            auto s = getCsSize(beatmap->Difficulty.CircleSize);
            this->size = s;
            a_start_size = s * APPROACH_CIRCLE_SIZE_MUL;
            this->rect.w = this->rect.h = s;

            this->approach_rect.w = this->approach_rect.h = a_start_size;

            auto pr = parent->getField();

            this->rect.x = this->x - s / 2 + pr.x;
            this->rect.y = this->y - s / 2 + pr.y;


            this->approach_rect.x = this->x - a_start_size / 2 + pr.x;
            this->approach_rect.y = this->y - a_start_size / 2 + pr.y;
        }

        ~Circle() {
        }

        void Render() override {
            auto t = parent->getTime();

            if (time + 120 < t) {
                //TODO
                this->parent->DestroyEntity(this);
                return;
            }

            auto r = Core::Engine::getRenderer();
            if (time < t)
                SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("hitcircle_active"), nullptr,
                               &rect);
            else {
                auto t_whole = time - startTime;
                auto t_passed = t - startTime;

                double k = (double) t_passed / (double) t_whole;

                if (k > 1) k = 1;

                recalc_approach_circle(k);

                SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("hitcircle_normal"), nullptr,
                               &rect);

                auto texture = Core::Engine::resourceManager->textures->getRawTexture("aproach_circle");
                SDL_SetTextureAlphaMod(texture, min((int) (k * 512), 255));
                SDL_RenderCopy(r, texture, nullptr, &this->approach_rect);
                //TODO: maybe reset texture alpha??????????
            }

            SDL_RenderDrawRect(r, &rect);
            //render the circle
        }

    private:
        void recalc_approach_circle(double progress) {
            auto scale = -(APPROACH_CIRCLE_SIZE_MUL - 1) * progress + APPROACH_CIRCLE_SIZE_MUL;
            auto sz = this->approach_rect.w = this->approach_rect.h = scale * this->size;

            auto pr = parent->getField();

            this->approach_rect.x = this->x - sz / 2 + pr.x;
            this->approach_rect.y = this->y - sz / 2 + pr.y;

        }
    };
}


