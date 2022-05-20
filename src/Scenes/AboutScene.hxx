#pragma once

#include "../include.hxx"

#include "../Core/Scenes/Scene.hxx"

#include "../Core/SdlExtensions.hxx"
#include "../Core/Entities/SpriteEntity.hxx"
#include "../Entities/UI/ButtonEntity.hxx"

#include "MenuScene.hxx"

class AboutScene: public Scene {
protected:
    Entities::SpriteEntity *instructions;
    ButtonEntity           *bExit;
public:
    AboutScene();
    void Activate() override;
};
