#include "PlayingFieldEntity.hxx"
#include <SDL2/SDL.h>

#include "../../Util/Osu.hxx"
#include "HitObjects/Circle.hxx"
#include "HitObjects/Slider.hxx"

using namespace Core;
using namespace std;
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

        this->field = {
                window_w / 2 - OSU_WIDTH / 2,
                window_h / 2 - OSU_HEIGHT / 2,
                OSU_WIDTH,
                OSU_HEIGHT
        };


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
                logher(INFO,"PFE") << "Adding ent @ " << globaltime << " for " << ho.time <<endlog;

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
                logher(DEBUG, "PFE render") << "Iterator OOB, exiting render loop." << i << ">=" <<this->n_ent << endlog;
                break;
            }
        }

    }
}