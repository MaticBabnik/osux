#pragma once

#include "../include.hxx"

#include "../Core/Scenes/Scene.hxx"

#include "../Core/SdlExtensions.hxx"
#include "../IO/Beatmap.hxx"
#include "../Entities/Osu/PlayingFieldEntity.hxx"
#include "../Entities/VolumeEntity.hxx"
#include "../Entities/UI/ButtonEntity.hxx"
#include "../IO/BeatmapCollection.hxx"
#include "MenuScene.hxx"
#include "BeatmapScene.hxx"

class BeatmapSelectionScene :  public Scene {
public:
    BeatmapSelectionScene();
    void Activate() override;
protected:
    int selectedIndex;

    Entities::TextEntity *tPlay;
    Entities::TextEntity *tBigFilename;

    ButtonEntity *bRefresh;
    ButtonEntity *bPlay;
    ButtonEntity *bAutoPlay;
    ButtonEntity *bExit;


    std::vector<ButtonEntity*> *bBeatmaps;


};
