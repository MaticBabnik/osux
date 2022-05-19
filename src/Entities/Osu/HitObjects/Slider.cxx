//
// Created by babnik on 4/16/22.
//

#include "Slider.hxx"

Osu::Slider::Slider(IO::HitObject *hitObject, IO::Beatmap *beatmap, Osu::PlayingFieldEntity *playingFieldEntity) {
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

    auto s = getCsSize(beatmap->Difficulty.CircleSize);

    this->rect.w = this->rect.h = s;
    this->rect.x = this->x - s / 2;
    this->rect.y = this->y - s / 2;

    this->rect = this->parent->toScreenRect(rect);

    this->n_points = hitObject->slider_args->points.size();
    this->points = new SDL_Point[n_points];

    for (int i = 0; i < this->n_points; i++) {
        auto op = hitObject->slider_args->points[i];
        this->points[i] = this->parent->toScreenCoords(op);
    }

    auto screen =Core::Engine::getPaintArea();
    this->surface = SDL_CreateRGBSurfaceWithFormat(0,screen.w,screen.h,32,SDL_PIXELFORMAT_RGBA32);

    auto sr = SDL_CreateSoftwareRenderer(surface);
    sux_thick_aa_line_mul(sr,this->points,this->n_points,parent->toRealPixels(sz+2),0xffffffff);
    sux_thick_aa_line_mul(sr,this->points,this->n_points,parent->toRealPixels(sz)  ,0xff000000);
    SDL_SetSurfaceBlendMode(this->surface,SDL_BLENDMODE_ADD);
    this->texture = SDL_CreateTextureFromSurface(Core::Engine::getRenderer(),surface);
}

void Osu::Slider::Render() {
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

    SDL_RenderCopy(r,texture, nullptr, nullptr);

    SDL_RenderCopy(r, Core::Engine::resourceManager->textures->getRawTexture("hitcircle_normal"),
                   nullptr, &rect);

}