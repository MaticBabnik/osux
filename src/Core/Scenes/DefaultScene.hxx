#pragma once

#include "../../include.hxx"
#include "Scene.hxx"
#include "../Engine.hxx"
#include "../Entities/TextEntity.hxx"

namespace Core {

    class DefaultScene : public Scene {
    protected:
        ulong initTime;
        bool giveUp;
        Scene *next;
        Entities::TextEntity *te;
    public:
        DefaultScene(Scene *nextScene);

        void Render();
    };
}


