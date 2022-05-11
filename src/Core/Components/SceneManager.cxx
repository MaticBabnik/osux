#include "SceneManager.hxx"

Core::SceneManager::SceneManager(Scene* defaultScene) {
    this->activeScene = defaultScene;
}

Core::SceneManager::~SceneManager() {
    delete activeScene;
}

Core::Scene *Core::SceneManager::getActiveScene() {
    return this->activeScene;
}

void Core::SceneManager::SwitchScene(Core::Scene *newScene) {
    delete activeScene;
    this->activeScene = newScene;
    this->activeScene->Activate();
}
