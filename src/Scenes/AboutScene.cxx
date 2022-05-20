#include "AboutScene.hxx"

using namespace Entities;

AboutScene::AboutScene() {
    this->instructions = nullptr;
    this->bExit = nullptr;
}

void AboutScene::Activate() {
    auto texture = Engine::resourceManager->textures->getRawTexture("guide");
    this->instructions = new SpriteEntity(texture,{0,0},-1,-1,false);
    this->AddEntity(instructions);

    auto roboto = Engine::resourceManager->fonts->get("roboto");
    auto bounds = Engine::getPaintArea();

    this->bExit = new ButtonEntity(roboto,{bounds.w-100,44},{255,128,128,255},{255,0,0,255},"< Back", false);
    this->bExit->setHandler([]() {
        Engine::sceneManager->queueSceneSwitch(new MenuScene());
    });
    this->AddEntity(bExit);
}
