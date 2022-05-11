#include "MenuScene.hxx"

SDL_Color normal = {255,255,255,255}, hover = {255,100,100,255};

void MenuScene::Activate() {
    this->AddEntity(new VolumeEntity());
}

MenuScene::MenuScene() {
    auto roboto = Engine::resourceManager->fonts->load("roboto","assets/roboto.ttf",20);
    auto bounds = Engine::getPaintArea();
    auto logo = Engine::resourceManager->textures->getRawTexture("logo");

    this->playT     = new Entities::TextEntity(roboto,{bounds.w/2,bounds.h/2 - 34},normal,"Play", false);
    this->settingsT = new Entities::TextEntity(roboto,{bounds.w/2+4,bounds.h/2 -10},normal,"Settings", false);
    this->aboutT     = new Entities::TextEntity(roboto,{bounds.w/2,bounds.h/2 +  14},normal,"About", false);

    this->logo      = new Entities::SpriteEntity(logo,{bounds.w/2 - 140,bounds.h/2},256,256,true);
    this->AddEntity(new WifeEntity);
    this->AddEntity(this->playT);
    this->AddEntity(this->settingsT);
    this->AddEntity(this->aboutT);
    this->AddEntity(this->logo);
}

void MenuScene::Render() {
    //this->logo->setSize(256+ pow(abs(3*fmod(SDL_GetTicks()*(3/930.0),1)),3));
    this->logo->setSize(256 + 10 * pow(sin(SDL_GetTicks() * (120.0/9300.0)),2));
    EntityCollection::Render();
}
