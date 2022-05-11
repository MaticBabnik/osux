
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
        SDL_Point *points;
        size_t n_points;
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

            this->n_points = hitObject->slider_args->points.size() + 1;
            this->points = new SDL_Point[n_points];

            this->points[0].x = this->x + pr.x;
            this->points[0].y = this->y + pr.y;
            logher(DEBUG, "Slider") << "n_points: "<< n_points << endlog;

            for (int i = 1; i < this->n_points; i++) {
                auto op = hitObject->slider_args->points[i-1];
                this->points[i].x = op.x + pr.x;
                this->points[i].y = op.y + pr.y;
            }

        }

        void Render() override {
            auto t = parent->getTime();

            if (time + 2000 < t) {
                this->parent->DestroyEntity(this);
                return;
            }
            auto r = Core::Engine::getRenderer();

            SDL_RenderDrawLines(r,this->points,this->n_points);

            SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("intro_1"),
                           nullptr, &rect);

        }

    };
}


