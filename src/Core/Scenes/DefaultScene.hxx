#pragma once

#include "../../include.hxx"
#include "Scene.hxx"
#include "../Engine.hxx"
#include "../Entities/TextEntity.hxx"

namespace Core {

    class DefaultScene : public Scene {
    protected:
        ulong initTime;
    public:
        DefaultScene();

        void Render();
    };
}


