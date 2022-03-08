#pragma once

#include "../include.hxx"
#include "../Core/Engine.hxx"
#include "../Core/Render.hxx"

class VolumeEntity : public Core::Entity {
protected:
    Core::Entities::TextEntity *tEnt;
    SDL_FPoint points[64];
    size_t n_points;
    int t = 0;

    Core::EventControl onScrollWheelEvent(SDL_Event *e);

public:
    VolumeEntity();

    virtual ~VolumeEntity() override;

    virtual void Render() override;

};
