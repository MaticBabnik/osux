#include "Scene.hxx"

Core::Scene::Scene() {
    this->eventManager = new EventManager();
}

Core::Scene::~Scene() {
    delete this->eventManager;
    this->eventManager = nullptr;
}

void Core::Scene::Activate() {
    logher(WARN,"sceneScene") << "Default activate called!" << endlog;
}
