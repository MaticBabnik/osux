//
// Created by babnik on 2/26/22.
//

#include "Circle.hxx"

Osu::Circle::Circle(IO::HitObject *hitObject, IO::Beatmap *beatmap, Osu::PlayingFieldEntity *playingFieldEntity) {
    this->parent = playingFieldEntity;
    this->x = hitObject->x;
    this->y = hitObject->y;
    this->time = hitObject->time;

    this->startTime = parent->getTime();

    auto s = getCsSize(beatmap->Difficulty.CircleSize);
    this->size = s;
    a_start_size = s * APPROACH_CIRCLE_SIZE_MUL;
    this->rect.w = this->rect.h = s;

    this->approach_rect.w = this->approach_rect.h = a_start_size;

    this->rect.x = this->x - s / 2;
    this->rect.y = this->y - s / 2;

    this->rect = this->parent->toScreenRect(this->rect);

    this->approach_rect.x = this->x - a_start_size / 2;
    this->approach_rect.y = this->y - a_start_size / 2;
    this->approach_rect = this->parent->toScreenRect(this->approach_rect);

    Core::Engine::sceneManager->getActiveScene()->eventManager->addEventListener(this, SDL_KEYDOWN, -1,
                                                                                 [this](SDL_Event *e) {
            if (!canBeHit)
                return Core::EventControl::NOT_HANDLED;
            switch (e->key.keysym.scancode) {
                case SDL_SCANCODE_Z:
                case SDL_SCANCODE_X:
                case SDL_SCANCODE_Y: {
                    // click
                    auto op = parent->getOsuMouseCoords();
                    auto d = Core::distance(op,{x, y});

                    if (d > (this->size / 2 + 2)){
                        return Core::EventControl::NOT_HANDLED;
                    }

                    auto offset = (long)parent->getTime() - this->time;
                    if (abs(offset) > 120) return Core::EventControl::NOT_HANDLED;

                    auto fS = Core::Engine::resourceManager->chunks->load("hit","assets/hit.wav");
                    Mix_PlayChannel(-1,fS,0);

                    this->canBeHit = false;

                    parent->scoreHitCircleHit(offset);
                    this->kms = true;
                    return Core::EventControl::CANCEL;
                }
                default:
                    return Core::EventControl::NOT_HANDLED;
            }
        });
}

void Osu::Circle::Render() {
    if (kms) {
        Core::Engine::sceneManager->getActiveScene()->eventManager->clearAllListeners(this);
        return;
        parent->DestroyEntity(this);
    }
    if (this->parent == nullptr) {
        logher(FATAL, "Circle") << "Parent is null" << endlog;
        return;
    }

    auto t = parent->getTime();


    if ((time - 120) < t && !canBeHit) {
        this->canBeHit = true;
    }

    if ((time + 120) < t) {

        this->canBeHit = false;
        auto fS = Core::Engine::resourceManager->chunks->load("fail","assets/fail.wav");
        Mix_PlayChannel(-1,fS,0);

        parent->scoreHitCircleMiss();
        Core::Engine::sceneManager->getActiveScene()->eventManager->clearAllListeners(this);
        this->parent->DestroyEntity(this);
        return;
    }

    auto r = Core::Engine::getRenderer();
    if (time < t)
        SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("hitcircle_active"), nullptr,
                       &rect);
    else {
        auto t_whole = time - startTime;
        auto t_passed = t - startTime;

        double k = (double) t_passed / (double) t_whole;

        if (k > 1) k = 1;

        recalc_approach_circle(k);

        SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("hitcircle_normal"), nullptr,
                       &rect);

        auto texture = Core::Engine::resourceManager->textures->getRawTexture("aproach_circle");
        SDL_SetTextureAlphaMod(texture, min((int) (k * 512), 255));
        SDL_RenderCopy(r, texture, nullptr, &this->approach_rect);
    }
}

void Osu::Circle::recalc_approach_circle(double progress) {
    auto scale = -(APPROACH_CIRCLE_SIZE_MUL - 1) * progress + APPROACH_CIRCLE_SIZE_MUL;
    auto sz = this->approach_rect.w = this->approach_rect.h = scale * this->size;


    this->approach_rect.x = this->x - sz / 2;
    this->approach_rect.y = this->y - sz / 2;
    this->approach_rect = this->parent->toScreenRect(this->approach_rect);
}

Osu::Circle::~Circle() {
}
