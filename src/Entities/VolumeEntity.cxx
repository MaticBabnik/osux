#include "VolumeEntity.hxx"

VolumeEntity::~VolumeEntity() {
    delete this->tEnt;
    Core::Engine::eventManager->clearAllListeners(this);
}


void VolumeEntity::Render() {
    if (t > 0) {
        auto r = Core::Engine::getRenderer();
        t--;
        tEnt->Render();
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        Core::Render::RenderArc(points, n_points, 1);
    }
}

VolumeEntity::VolumeEntity() {
    auto f = Core::Engine::resourceManager->fonts->load("sp7", "assets/sp7.ttf", 20);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Point o = {100, 100};
    tEnt = new Core::Entities::TextEntity(f, o, white, "100");

    Core::Engine::eventManager->addEventListener(this, SDL_MOUSEWHEEL, 0,
                                                 [this](SDL_Event *e) {
                                                     return this->onScrollWheelEvent(e);
                                                 });
    n_points = 0;
}


Core::EventControl VolumeEntity::onScrollWheelEvent(SDL_Event *e) {
    auto scroll = e->wheel.y;
    if (scroll != 0) {
        t = 100;
        auto v = Mix_VolumeMusic(-1);
        Mix_VolumeMusic(v + scroll);
        tEnt->setText(std::to_string(v + scroll));
        n_points = Core::Render::SetupArc({105, 107}, 20.0f, (float) v / 100.0f, points, 64);
    }
    return Core::HANDLED;
}
