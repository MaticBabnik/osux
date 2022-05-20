#pragma once

#include "../include.hxx"

#include "../Core/Scenes/Scene.hxx"

#include "../Core/SdlExtensions.hxx"
#include "../IO/Beatmap.hxx"
#include "../Entities/Osu/PlayingFieldEntity.hxx"
#include "../Entities/VolumeEntity.hxx"
#include "../Entities/UI/ButtonEntity.hxx"
#include "../IO/Config.hxx"
#include "MenuScene.hxx"

static SDL_Point resolutions[] = {
        {800,600},
        {1024,768},
        {1280,720},
        {1920,1080},
        {2560,1440},
        {3840,2160},
        {1080, 1920}
};

constexpr auto n_res = sizeof(resolutions) / sizeof(SDL_Point);

class SettingsScene :  public Scene {
protected:
    Entities::TextEntity *tTitle,*tResolution,*tRestart;
    ButtonEntity *bFullscreen, *bSave, *bExit;
    vector<ButtonEntity*> *bResolutions;
    IO::OsuxConfig ocfg;
public:
    SettingsScene(IO::Config *cfg);
    void Activate() override;
};