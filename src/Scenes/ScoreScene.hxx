#pragma once

#include "../include.hxx"

#include "../Core/Scenes/Scene.hxx"

#include "../Core/SdlExtensions.hxx"
#include "../Core/Entities/SpriteEntity.hxx"
#include "../Entities/UI/ButtonEntity.hxx"

#include "MenuScene.hxx"

class ScoreScene: public Scene {
protected:
    Entities::TextEntity *score,*acc,*maxC;
    ButtonEntity           *bExit;
    std::string sscore,sacc,scombo;
public:
    ScoreScene(int score, double acc, int maxCombo);
    void Activate() override;
};
