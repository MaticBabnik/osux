#include "PlayingFieldEntity.hxx"
#include "HitObjects/Circle.hxx"
#include "HitObjects/Slider.hxx"
#include "../../Scenes/BeatmapScene.hxx"
#include "../../Scenes/BeatmapSelectionScene.hxx"
#include "../../Scenes/ScoreScene.hxx"

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

        obj_h = 0;
        obj_t = 0;
        obj_m = 0;
        combo = 0;
        score = 0;
        maxCombo = 0;
        et = 100000;

        auto w = Engine::getWindow();
        int window_w, window_h;

        SDL_GetWindowSize(w, &window_w, &window_h);

        this->preempt = (int) getArFadeinTime(beatmap->Difficulty.ApproachRate);
        this->index = 0;
        this->tpIndex = 0;

        while (tpIndex < beatmap->TimingPoints.size() && beatmap->TimingPoints[tpIndex].time < 1) {
            auto tp = beatmap->TimingPoints[tpIndex];
            if (tp.uninherited) {
                lastTp = tp.beatLength;
                lastUTp = tp.beatLength;
            } else {
                lastTp = ((-100 / tp.beatLength) * lastUTp);
            }
            tpIndex++;
        }

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

        Engine::sceneManager->getActiveScene()->eventManager->addEventListener(this, SDL_KEYDOWN, 0,
                                                                               [this](SDL_Event *e) {
                                                                                   switch (e->key.keysym.scancode) {
                                                                                       case SDL_SCANCODE_Q:
                                                                                       case SDL_SCANCODE_ESCAPE:
                                                                                           //exit
                                                                                           this->canFreeBeatmap = true;
                                                                                           Engine::sceneManager->queueSceneSwitch(
                                                                                                   new BeatmapSelectionScene());

                                                                                           return EventControl::HANDLED;

                                                                                       case SDL_SCANCODE_R:
                                                                                           //reload
                                                                                           this->canFreeBeatmap = false;
                                                                                           //why tf do i have to cast it????
                                                                                           Engine::sceneManager->queueSceneSwitch(
                                                                                                   (Scene *) (new BeatmapScene(
                                                                                                           this->beatmap)));
                                                                                           return EventControl::HANDLED;
                                                                                       default:
                                                                                           return EventControl::NOT_HANDLED;

                                                                                   }
                                                                               });


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
            if (this->beatmap->HitObjects.size() <= this->index) {
                if (globaltime > et) {
                    Engine::sceneManager->queueSceneSwitch(new ScoreScene(score, obj_h / (double) obj_t, combo));
                }

                break;
            }

            while (tpIndex < beatmap->TimingPoints.size() && beatmap->TimingPoints[tpIndex].time < 1) {
                auto tp = beatmap->TimingPoints[tpIndex];
                if (tp.uninherited) {
                    lastTp = tp.beatLength;
                    lastUTp = tp.beatLength;
                } else {
                    lastTp = ((-100 / tp.beatLength) * lastUTp);
                }
                tpIndex++;
            }

            auto ho = this->beatmap->HitObjects[this->index];
            if (ho.time - this->preempt < globaltime) { //hitobject should be rendered
                et = ho.time + 2000;
                switch (ho.type) {
                    case IO::HitObjectType::HitCircle:
                        this->AddEntity(new Circle(&ho, beatmap, this));
                        index++;
                        break;
                    case IO::HitObjectType::Slider:
                        // no time
                        //this->AddEntity(new Slider(&ho, beatmap, this));
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
        return {(int) ((in.x - field.x) / osupx_ratio), (int) ((in.y - field.y) / osupx_ratio)};
    }

    SDL_Point PlayingFieldEntity::toScreenCoords(SDL_Point in) {
        return {(int) (in.x * osupx_ratio + field.x), (int) (in.y * osupx_ratio + field.y)};
    }

    SDL_Rect PlayingFieldEntity::toScreenRect(SDL_Rect in) {
        return {(int) (in.x * osupx_ratio + field.x), (int) (in.y * osupx_ratio + field.y), (int) (in.w * osupx_ratio),
                (int) (in.h * osupx_ratio)};
    }

    void PlayingFieldEntity::scoreHitCircleHit(long time) {
        obj_t++;
        obj_h++;
        combo++;
        if (combo > maxCombo) maxCombo = combo;
        score += ((double) (120 - abs(time)) * (double) (log(combo) + 1));

        auto *p = dynamic_cast<BeatmapScene *>(parent);

        p->SetCombo(combo);
        p->SetScore(score);
        p->SetAcc((double) obj_h / obj_t);

        logher(INFO, "SCORE") << "Hit with offset " << time << endlog;
    }

    void PlayingFieldEntity::scoreHitCircleMiss() {
        obj_t++;
        obj_m++;
        combo = 0;

        auto *p = dynamic_cast<BeatmapScene *>(parent);
        p->SetCombo(combo);
        p->SetAcc((double) obj_h / obj_t);

        logher(INFO, "SCORE") << "Missed circle" << endlog;
    }

    void PlayingFieldEntity::scoreSliderStart() {
        logher(INFO, "SCORE") << "HitSliderStart" << endlog;

    }

    void PlayingFieldEntity::scoreSliderPercentage(int percentage) {
        logher(INFO, "SCORE") << "Slider end with " << percentage << "%" << endlog;
    }

    void PlayingFieldEntity::scoreSpinnerPass(int score) {
        logher(INFO, "SCORE") << "Spinner " << score << endlog;

    }

    void PlayingFieldEntity::scoreSpinnerMiss() {
        logher(INFO, "SCORE") << "Missed spinner" << endlog;
    }

    PlayingFieldEntity::~PlayingFieldEntity() {
        if (this->canFreeBeatmap) delete this->beatmap;
    }

    SDL_Point PlayingFieldEntity::getOsuMouseCoords() {
        SDL_Point p;
        SDL_GetMouseState(&p.x, &p.y);
        return toOsuCoords(p);
    }

    double PlayingFieldEntity::getSliderPos(int t) {
        return 100 * beatmap->Difficulty.SliderMultiplier * (t / lastTp);
    }

//    double PlayingFieldEntity::getCurrentSliderSpeed() {
//        return beatmap->Difficulty.SliderMultiplier * lastTp;
//    }
}