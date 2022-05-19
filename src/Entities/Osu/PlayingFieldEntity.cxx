#include "PlayingFieldEntity.hxx"
#include <SDL2/SDL.h>

#include "../../Util/Osu.hxx"
#include "HitObjects/Circle.hxx"
#include "HitObjects/Slider.hxx"

using namespace Core;
using namespace std;

/*
 * 640x480
 * 512x384
 */

namespace Osu {
    uint PlayingFieldEntity::getTime() const {
        return globaltime;
    }

    SDL_Rect PlayingFieldEntity::getField() {
        return field;
    }

    PlayingFieldEntity::PlayingFieldEntity(IO::Beatmap *beatmap) {
        auto w = Engine::getWindow();
        int window_w, window_h;

        SDL_GetWindowSize(w, &window_w, &window_h);

        this->preempt = (int) getArFadeinTime(beatmap->Difficulty.ApproachRate);
        this->index = 0;

        double aspect_ratio = (double) window_w / (double) window_h;

        this->field = {0, 0, 0, 0};

        if (aspect_ratio < 4.0 / 3.0) {
            // "tall" layout
            int nw = window_w * 0.8;
            this->field.w = nw;
            this->field.h = (double) nw / 4.0 * 3.0;
        } else {
            // "wide" layout
            int nh = window_h * 0.8;
            this->field.h = nh;
            this->field.w = (double) nh / 3.0 * 4.0;
        }

        this->field.x = (window_w - this->field.w) / 2;
        this->field.y = (window_h - this->field.h) / 2;

        this->osupx_ratio = this->field.w / 512.0;

        this->beatmap = beatmap;
    }

    void PlayingFieldEntity::Render() {
        [[unlikely]]
        if (globaltime == -1) {
            globaltime = 0;
            gtOffset = SDL_GetTicks();
        } else {
            globaltime = SDL_GetTicks() - gtOffset;
        }

        auto r = Engine::getRenderer();

        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderDrawRect(r, &this->field);

        while (true) {
            if (this->beatmap->HitObjects.size() < this->index) break;

            auto ho = this->beatmap->HitObjects[this->index];
            if (ho.time - this->preempt < globaltime) { //hitobject should be rendered
                logher(INFO, "PFE") << "Adding ent @ " << globaltime << " for " << ho.time << endlog;

                switch (ho.type) {
                    case IO::HitObjectType::HitCircle:
                        this->AddEntity(new Circle(&ho, beatmap, this));
                        index++;
                        break;
                    case IO::HitObjectType::Slider:
                        this->AddEntity(new Slider(&ho, beatmap, this));
                        index++;
                        break;
                    default:
                        index++;
                        break;
                }
            } else {
                break;
            }

        }

        auto iterator = this->entities->begin();
        size_t i = 0;
        auto sz = this->n_ent;

        while (iterator != this->entities->end()) {
            (*iterator)->Render();
            iterator++;
            i++;
            if (i > this->n_ent) {
                logher(DEBUG, "PFE render") << "Iterator OOB, exiting render loop." << i << ">=" << this->n_ent
                                            << endlog;
                break;
            }
        }

    }

    int PlayingFieldEntity::toRealPixels(int osupixel) {
        return osupixel * osupx_ratio;
    }

    double PlayingFieldEntity::toRealPixels(double osupixel) {
        return osupixel * osupx_ratio;
    }

    int PlayingFieldEntity::toOsuPixels(int osupixel) {
        return osupixel / osupx_ratio;
    }

    double PlayingFieldEntity::toOsuPixels(double osupixel) {
        return osupixel / osupx_ratio;
    }

    SDL_Point PlayingFieldEntity::toOsuCoords(SDL_Point in) {
        return {(int) ((field.x - in.x) / osupx_ratio), (int) ((field.y - in.y) / osupx_ratio)};
    }

    SDL_Point PlayingFieldEntity::toScreenCoords(SDL_Point in) {
        return {(int) (in.x * osupx_ratio + field.x), (int) (in.y * osupx_ratio + field.y)};
    }

    SDL_Rect PlayingFieldEntity::toScreenRect(SDL_Rect in) {
        return {(int) (in.x * osupx_ratio + field.x), (int) (in.y * osupx_ratio + field.y), (int) (in.w * osupx_ratio),
                (int) (in.h * osupx_ratio)};
    }
}