#include "PlayingFieldEntity.hxx"
#include <SDL2/SDL.h>

#include "../../Util/Osu.hxx"
#include "HitObjects/Circle.hxx"

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
            if (ho.type != IO::HitObjectType::HitCircle) {
                index++;
                continue;
            }
            if (ho.time - this->preempt < globaltime) { //hitobject should be rendered
                this->AddEntity(new Circle(&ho, beatmap, this));
                index++;
            } else {
                break;
            }

        }

        for (Core::Entity *e: *this->entities) {
            e->Render();
        }
    }
}