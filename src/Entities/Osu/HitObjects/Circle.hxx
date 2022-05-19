
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
        Circle(IO::HitObject *hitObject, IO::Beatmap *beatmap, PlayingFieldEntity *playingFieldEntity);

        void Render() override;

    private:
        void recalc_approach_circle(double progress);
    };
}


