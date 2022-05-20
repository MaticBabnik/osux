#include "SceneManager.hxx"

Core::SceneManager::SceneManager(Scene *defaultScene) {
    this->activeScene = defaultScene;
    this->nextScene = nullptr;
}

Core::SceneManager::~SceneManager() {
    delete activeScene;
}

Core::Scene *Core::SceneManager::getActiveScene() {
    return this->activeScene;
}

void Core::SceneManager::switchScene(Core::Scene *newScene) {
    delete activeScene;
    this->activeScene = newScene;
    this->activeScene->Activate();
}

void Core::SceneManager::queueSceneSwitch(Core::Scene *newScene) {
    if (newScene != nullptr) this->nextScene = newScene;
}

void Core::SceneManager::switchSafePoint() {
    if (nextScene != nullptr)
    {
        switchScene(nextScene);
        nextScene = nullptr;
    }

}
