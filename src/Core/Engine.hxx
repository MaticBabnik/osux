#pragma once

#include "../include.hxx"

#include "SdlExtensions.hxx"

#include "Entity.hxx"
#include "EntityCollection.hxx"

#include "../IO/Logger.hxx"

#include "Components/ResourceManager.hxx"
#include "Components/SceneManager.hxx"

#include "Entities/TextEntity.hxx"
#include "Entities/WifeEntity.hxx" //best entity ever
#include "Entities/SpriteEntity.hxx"

namespace Core {
    //TODO: scene system, to avoid having to handle multiple entities here
    class Entity;

    class EntityCollection;

    class Engine {
    protected:
        static inline SDL_Window *window;
        static inline SDL_Renderer *renderer;
        static inline SDL_BlendMode slider_blend;

    public:
        static inline ResourceManager *resourceManager;
        static inline SceneManager* sceneManager;

        static SDL_Window *getWindow();

        static SDL_Renderer *getRenderer();

        static SDL_Rect getPaintArea();
        static SDL_BlendMode *getSliderBlend();
        [[noreturn]] static void RunLoop(Scene *firstScene);

        static void Init(uint w, uint h, bool fullscreen);

        static void Free();

    };

}
