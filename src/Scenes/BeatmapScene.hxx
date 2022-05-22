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
    Entities::TextEntity *score,*acc,*combo;

    bool playMusic;
    Beatmap *beatmap;
public:

    void SetCombo(int c);
    void SetAcc(double a);
    void SetScore(int s);

    BeatmapScene(Beatmap *bm);

    ~BeatmapScene();

    void Activate() override;

    void Render();

};
