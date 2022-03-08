#include "WifeEntity.hxx"

namespace Core {

    void WifeEntity::Render() {
        SDL_RenderCopy(Core::Engine::getRenderer(), fbk, nullptr, nullptr);
    }

    WifeEntity::WifeEntity() {
        Core::Engine::resourceManager->textures->load("wife", "../assets/wife.png");
        this->fbk = Core::Engine::resourceManager->textures->getRawTexture("wife");
        SDL_SetTextureAlphaMod(fbk, 0x44);
    }

    WifeEntity::~WifeEntity() {
        logher(FATAL, "Wife") << "Wife never dies" << endlog;
    }
}
