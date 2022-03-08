#pragma once

#include "../include.hxx"

#include "Entity.hxx"
#include "EntityCollection.hxx"

#include "../IO/Logger.hxx"

#include "Components/ResourceManager.hxx"
#include "Components/EventManager.hxx"

#include "Entities/TextEntity.hxx"
#include "Entities/WifeEntity.hxx" //best entity ever

namespace Core {
    //TODO: scene system, to avoid having to handle multiple entities here
    class Entity;

    class EntityCollection;

    class Engine {
    protected:
        static inline SDL_Window *window;
        static inline SDL_Renderer *renderer;

    public:
        static inline ResourceManager *resourceManager;

        static inline EventManager *eventManager;

        static inline EntityCollection *activeScene;

        static SDL_Window *getWindow();

        static SDL_Renderer *getRenderer();

        [[noreturn]] static void RunLoop();

        static void Init(uint w, uint h);

        static void Free();

    };

}
