#include "MenuScene.hxx"

SDL_Color normal = {255, 255, 255, 255}, hover = {255, 100, 192, 255};

void MenuScene::Activate() {
    auto roboto = Engine::resourceManager->fonts->load("roboto", "assets/roboto.ttf", 20);
    auto bounds = Engine::getPaintArea();

    this->playT =     new ButtonEntity(roboto, {bounds.w / 2, bounds.h / 2 - 34}, normal, hover, "Play", false);
    this->settingsT = new ButtonEntity(roboto, {bounds.w / 2, bounds.h / 2 - 10}, normal, hover, "Settings", false);
    this->aboutT =    new ButtonEntity(roboto, {bounds.w / 2, bounds.h / 2 + 14}, normal, hover, "About", false);
    this->exitT =     new ButtonEntity(roboto, {bounds.w / 2, bounds.h / 2 + 38}, normal, hover, "Exit", false);

    this->playT->setHandler([this]() {
        // instantly switching scenes would cause a segfault, so we use queueSceneSwitch
    });

    this->settingsT->setHandler([this]() {
        // instantly switching scenes would cause a segfault, so we use queueSceneSwitch
        Engine::sceneManager->queueSceneSwitch(new SettingsScene(Engine::configManager));
    });

    this->aboutT->setHandler([this]() {
        Engine::sceneManager->queueSceneSwitch(new AboutScene());
    });

    this->exitT->setHandler([](){
        exit(0);
    });

    this->AddEntity(this->playT);
    this->AddEntity(this->settingsT);
    this->AddEntity(this->aboutT);
    this->AddEntity(this->exitT);

    this->AddEntity(new VolumeEntity());
}

MenuScene::MenuScene() {
    auto bounds = Engine::getPaintArea();
    auto logo = Engine::resourceManager->textures->getRawTexture("logo");

    this->logo = new Entities::SpriteEntity(logo, {bounds.w / 2 - 140, bounds.h / 2}, 256, 256, true);
    this->AddEntity(new WifeEntity);
    this->AddEntity(this->logo);
}

void MenuScene::Render() {
    //this->logo->setSize(256+ pow(abs(3*fmod(SDL_GetTicks()*(3/930.0),1)),3));
    this->logo->setSize(256 + 10 * pow(sin(SDL_GetTicks() * (120.0 / 9300.0)), 2));
    EntityCollection::Render();
}
