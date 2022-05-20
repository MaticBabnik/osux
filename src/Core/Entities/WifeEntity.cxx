#include "WifeEntity.hxx"

namespace Core {
    //TODO: refactor to BackgroundEntity
    void WifeEntity::Render() {
        auto r = Engine::getPaintArea();
        SDL_RenderCopy(Core::Engine::getRenderer(), fbk, &r, nullptr);
    }

    WifeEntity::WifeEntity() {
        Core::Engine::resourceManager->textures->load("wife", "../assets/background.png");
        this->fbk = Core::Engine::resourceManager->textures->getRawTexture("wife");
        SDL_SetTextureAlphaMod(fbk, 0x44);
    }

    WifeEntity::~WifeEntity() {
    }
}
