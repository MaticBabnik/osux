//
// Created by babnik on 5/4/22.
//

#include "DefaultScene.hxx"

void Core::DefaultScene::Render()
    {
        Scene::Render();
        if (initTime + 2000 > SDL_GetTicks()) {
            //Engine::s
        }
    }

Core::DefaultScene::DefaultScene()  {
    SDL_Color white = {255, 255, 255, 255};
    auto te = new Entities::TextEntity( Engine::resourceManager->fonts->load("sp7", "assets/sp7.ttf", 20),
                                        {200, 200}, white ,
                                        "oSUX");
    this->AddEntity(te);
    initTime = SDL_GetTicks();
}