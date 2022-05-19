
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
        SDL_Texture *texture;
        SDL_Surface *surface;
    public:
        Slider(IO::HitObject *hitObject, IO::Beatmap *beatmap, PlayingFieldEntity *playingFieldEntity);

        void Render() override;

    };
}
