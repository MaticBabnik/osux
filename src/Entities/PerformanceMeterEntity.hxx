#pragma once

#include "../include.hxx"
#include "Osu/PlayingFieldEntity.hxx"

class PerformanceMeterEntity : Core::Entity {
public:
    PerformanceMeterEntity();

    ~PerformanceMeterEntity();

    void update(float deltaTime);

    void render(SDL_Renderer &renderer);

};