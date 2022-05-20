#pragma once

#include "../include.hxx"

#include "../Core/Scenes/Scene.hxx"

#include "../Core/SdlExtensions.hxx"
#include "../IO/Beatmap.hxx"
#include "../Entities/Osu/PlayingFieldEntity.hxx"
#include "../Entities/VolumeEntity.hxx"
#include "../Entities/UI/ButtonEntity.hxx"
#include "SettingsScene.hxx"
#include "AboutScene.hxx"

using namespace Core;
using namespace IO;
using namespace Osu;

class MenuScene : public Scene {
protected:
    ButtonEntity *playT,*settingsT,*aboutT,*exitT;
    Entities::SpriteEntity *logo;
public:
    MenuScene();
    void Activate() override;
    void Render() override;

};
