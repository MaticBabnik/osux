#pragma once

#include "../include.hxx"

#include "../Core/Scenes/Scene.hxx"

#include "../Core/SdlExtensions.hxx"
#include "../IO/Beatmap.hxx"
#include "../Entities/Osu/PlayingFieldEntity.hxx"
#include "../Entities/VolumeEntity.hxx"

using namespace Core;
using namespace IO;
using namespace Osu;

class SliderTestScene : public Scene {
protected:
    SDL_Point points[32];
public:
    SliderTestScene();
    void Activate() override;
    void Render() override;

};
