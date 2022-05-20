#pragma once

#include "../../include.hxx"
#include "../../Core/Entities/TextEntity.hxx"
#include "../../Core/Math2D.hxx"

using namespace Core;

class ButtonEntity: public Entities::TextEntity {
public:
    ButtonEntity(TTF_Font *font, SDL_Point origin, SDL_Color color, SDL_Color hoverColor, std::string text,bool centered = true);
    ~ButtonEntity();
    void Render() override;
    void setHandler(const function<void(void)> &hnd);
protected:
    function<void(void)> handler;
    bool mouseInside;
};
