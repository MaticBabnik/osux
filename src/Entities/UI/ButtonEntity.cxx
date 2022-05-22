#include <utility>

#include "ButtonEntity.hxx"



void ButtonEntity::setHandler(const function<void(void)> &hnd) {
    this->handler = hnd;
}

ButtonEntity::~ButtonEntity() {

}

ButtonEntity::ButtonEntity(TTF_Font *font, SDL_Point origin, SDL_Color color, SDL_Color hoverColor, std::string text, bool centered)
        : TextEntity(font, origin, color, text, centered) {
    this->mouseInside = false;

    Engine::sceneManager->getActiveScene()->eventManager->addEventListener(this,SDL_MOUSEMOTION,0,[this,color,hoverColor] (SDL_Event *e) {
        auto _mouseInside = Core::hittest(this->getRect(),{e->motion.x,e->motion.y});

        if (this->mouseInside != _mouseInside) {
            this->setColor(_mouseInside ? hoverColor: color);
            this->mouseInside = _mouseInside;
        }

        return EventControl::NOT_HANDLED;
    });

    Engine::sceneManager->getActiveScene()->eventManager->addEventListener(this,SDL_MOUSEBUTTONDOWN,0,[this] (SDL_Event *e) {
        SDL_Point p;
        SDL_GetMouseState(&p.x, &p.y);

        if (Core::hittest(this->getRect(), p)) {
            handler(); // i barely even know her :)
            return EventControl::HANDLED;
        } else {
            return EventControl::NOT_HANDLED;
        }
    });
}

void ButtonEntity::Render() {
    Entities::TextEntity::Render();
}
