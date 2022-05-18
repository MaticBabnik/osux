
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
        double sz;
        bool kms; //kill myself
    public:
        Slider(IO::HitObject *hitObject, IO::Beatmap *beatmap, PlayingFieldEntity *playingFieldEntity) {
            this->parent = playingFieldEntity;

            if(hitObject->slider_args->repeat == -1) {
                logher(WARN,"HitObject") << "Unsupported Slider" << endlog;
                this->kms = true;
                return;
            }
            this->kms = false;
            //setup the draw area

            this->x = hitObject->x;
            this->y = hitObject->y;
            this->time = hitObject->time;

            this->sz = getCsSize(beatmap->Difficulty.CircleSize) / 2;

            auto s = 32;

            this->rect.w = this->rect.h = s;
            auto pr = parent->getField();

            this->rect.x = this->x - s / 2 + pr.x;
            this->rect.y = this->y - s / 2 + pr.y;

            this->n_points = hitObject->slider_args->points.size();
            this->points = new SDL_Point[n_points];


            for (int i = 0; i < this->n_points; i++) {
                auto op = hitObject->slider_args->points[i];
                this->points[i].x = op.x + pr.x;
                this->points[i].y = op.y + pr.y;
            }


        }

        void Render() override {
            auto t = parent->getTime();

            if (this->kms) {
                this->parent->DestroyEntity(this);
                return;
            }

            if (time + 2000 < t) {
                this->parent->DestroyEntity(this);
                return;
            }
            auto r = Core::Engine::getRenderer();

            //SDL_RenderDrawLines(r,this->points,this->n_points);

            sux_thick_aa_line_mul(r,this->points,this->n_points,sz+2,0xffffffff);
            sux_thick_aa_line_mul(r,this->points,this->n_points,sz,0xff000000);

            SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("intro_1"),
                           nullptr, &rect);

        }

    };
}


