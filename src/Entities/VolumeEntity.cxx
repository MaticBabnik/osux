#include "VolumeEntity.hxx"

VolumeEntity::~VolumeEntity() {
    delete this->tEnt;
    delete this->tEnt2;
    Core::Engine::eventManager->clearAllListeners(this);
}


void VolumeEntity::Render() {
    if (t > 0) {
        auto r = Core::Engine::getRenderer();
        t--;
        tEnt->Render();
        tEnt2->Render();
        aacircleRGBA(r,100,100,22,255,255,255,255);
        aaFilledPolygonRGBA(r, this->px, this->py, n_points, 255, 0, 0, 255);
    }
}

VolumeEntity::VolumeEntity() {
    auto f = Core::Engine::resourceManager->fonts->load("sp7", "assets/sp7.ttf", 20);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Point o = {100, 100};
    tEnt = new Core::Entities::TextEntity(f, o, white, "100");
    tEnt2 = new Core::Entities::TextEntity(f,{130,95},white,"Master volume",false);
    Core::Engine::eventManager->addEventListener(this, SDL_MOUSEWHEEL, 0,
                                                 [this](SDL_Event *e) {
                                                     return this->onScrollWheelEvent(e);
                                                 });

    n_points = 0;
}


Core::EventControl VolumeEntity::onScrollWheelEvent(SDL_Event *e) {
    auto scroll = e->wheel.y;
    if (scroll != 0) {
        t = 300;
        auto v = Mix_VolumeMusic(-1) + scroll;
        v = max(min(v, 100), 0); //clamp volume
        Mix_VolumeMusic( v);

        tEnt->setText(std::to_string(v));

        n_points = Core::Render::SetupArc({100, 100}, 20, 24, v / 100.0, px, py, VolumeEntity::max_points);
    }
    return Core::HANDLED;
}
