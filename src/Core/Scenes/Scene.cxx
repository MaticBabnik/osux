#include "Scene.hxx"

Core::Scene::Scene() {
    this->eventManager = new EventManager();
}

Core::Scene::~Scene() {
    delete this->eventManager;
}
