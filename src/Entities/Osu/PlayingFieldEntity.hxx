#pragma once

#include "SDL2/SDL.h"

#include "../../Core/Engine.hxx"
#include "../../IO/Beatmap.hxx"

#define OSU_WIDTH (16 * 32)
#define OSU_HEIGHT (12 * 32)

namespace Osu {

    class PlayingFieldEntity : public Core::EntityCollection {
    public:
        PlayingFieldEntity(IO::Beatmap *beatmap);

        uint getTime() const;

        SDL_Rect getField();

        void Render() override;

    protected:
        SDL_Rect field;
        IO::Beatmap *beatmap;
        int preempt;
        int index;
        long long globaltime = -1;
        uint gtOffset = 0;


    };


}