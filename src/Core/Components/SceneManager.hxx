#pragma once

#include "../Scenes/Scene.hxx"
//#include "../Scenes/DefaultScene.hxx"

namespace Core {
    class SceneManager {
    protected:
        Scene *activeScene;
    public:
        SceneManager(Scene* defaultScene);
        ~SceneManager();

        Scene *getActiveScene();

        void SwitchScene(Scene* newScene);
    };
}