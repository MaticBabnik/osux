#pragma once

#include "../Scenes/Scene.hxx"
//#include "../Scenes/DefaultScene.hxx"

namespace Core {
    class SceneManager {
    protected:
        Scene *activeScene;
        Scene *nextScene;
    public:
        SceneManager(Scene* defaultScene);
        ~SceneManager();

        Scene *getActiveScene();

        void switchScene(Scene* newScene);
        void queueSceneSwitch(Scene* newScene);
        void switchSafePoint();
    };
}