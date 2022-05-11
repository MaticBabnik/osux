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

class MenuScene : public Scene {
protected:
    Entities::TextEntity *playT,*settingsT,*aboutT;
    Entities::SpriteEntity *logo;
public:
    MenuScene();
    void Activate() override;
    void Render() override;

};
