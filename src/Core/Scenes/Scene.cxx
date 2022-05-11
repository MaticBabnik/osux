#include "Scene.hxx"

Core::Scene::Scene() {
    this->eventManager = new EventManager();
}

Core::Scene::~Scene() {
    delete this->eventManager;
}

void Core::Scene::Activate() {
    logher(WARN,"sceneScene") << "Default activate called!" << endlog;
}
