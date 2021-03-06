#pragma once

#include "../../include.hxx"
#include "../../Core/Engine.hxx"
#include "../../IO/Beatmap.hxx"

#define OSU_WIDTH (16 * 32)
#define OSU_HEIGHT (12 * 32)

namespace Osu {

    class PlayingFieldEntity : public Core::EntityCollection {
    public:
        PlayingFieldEntity(IO::Beatmap *beatmap);
        ~PlayingFieldEntity() override;
        uint getTime() const;
        SDL_Rect getField();
        void Render() override;

        int toRealPixels(int osupixel);
        double toRealPixels(double osupixel);

        int toOsuPixels(int osupixel);
        double toOsuPixels(double osupixel);

        SDL_Point toOsuCoords(SDL_Point in);
        SDL_Point toScreenCoords(SDL_Point in);

        SDL_Point getOsuMouseCoords();

        SDL_Rect toScreenRect(SDL_Rect in);

        double getSliderPos(int t);
        IO::TimingPoint getMapTimedParams(long time);

        void scoreHitCircleHit(long time);
        void scoreHitCircleMiss();
        void scoreSliderStart();
        void scoreSliderPercentage(int percentage);

        void scoreSpinnerPass(int score);
        void scoreSpinnerMiss();

    protected:
        SDL_Rect field;
        IO::Beatmap *beatmap;
        int preempt;
        int index;
        int tpIndex;
        double lastUTp;
        double lastTp;
        long long globaltime = -1;
        uint gtOffset = 0;
        double osupx_ratio;
        long et;

        int obj_h;
        int obj_m;
        int obj_t;
        int combo,maxCombo;
        int score;

        bool canFreeBeatmap = true;

    };


}