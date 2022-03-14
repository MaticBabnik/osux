#pragma once

#include "../include.hxx"
#include "../Core/Engine.hxx"
#include "../Core/Render.hxx"

class VolumeEntity : public Core::Entity {
protected:
    const inline static size_t max_points = 48;
    Core::Entities::TextEntity *tEnt, *tEnt2;
    double px[max_points];
    double py[max_points];
    size_t n_points;
    int t = 0;

    Core::EventControl onScrollWheelEvent(SDL_Event *e);

public:
    VolumeEntity();

    virtual ~VolumeEntity() override;

    virtual void Render() override;

};
