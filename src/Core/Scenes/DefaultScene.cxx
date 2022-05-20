//
// Created by babnik on 5/4/22.
//

#include "DefaultScene.hxx"

constexpr auto text = "osuX by Matic Babnik";

void Core::DefaultScene::Render() {
    ulong sceneTime = SDL_GetTicks() - initTime;

    Scene::Render();
    if (sceneTime>2000 && !giveUp) {
        if (next != nullptr) {
            Engine::sceneManager->switchScene(next);
            return; // return, since any use of `this` after switching scenes is prolly UB
        }else {
            giveUp = true;
            constexpr SDL_Color red = {255,0,0,255};
            this->te->setColor(red);
            this->te->setText("No scene!");
        }

    }
}

Core::DefaultScene::DefaultScene(Scene *nextScene) {
    this->giveUp = false;
    this->next = nextScene;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect w = Engine::getPaintArea();

    this->te = new Entities::TextEntity(Engine::resourceManager->fonts->load("roboto", "assets/roboto.ttf", 20),
                                       {w.w / 2, w.h / 2}, white,
                                       text);
    this->AddEntity(te);
    initTime = SDL_GetTicks();
}