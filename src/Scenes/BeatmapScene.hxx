#pragma once

#include "../include.hxx"

#include "../Core/Scenes/Scene.hxx"

#include "../IO/Beatmap.hxx"
#include "../Entities/Osu/PlayingFieldEntity.hxx"
#include "../Entities/VolumeEntity.hxx"

using namespace Core;
using namespace IO;
using namespace Osu;

class BeatmapScene : public Scene {
protected:
PlayingFieldEntity *playingField;
bool playMusic;
Beatmap *beatmap;
public:
    BeatmapScene(Beatmap *bm);
    void Activate() override;
    void Render();

};
