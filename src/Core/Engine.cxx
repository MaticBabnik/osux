#include "Engine.hxx"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>


/*
 * TODO: Scene system
 * TODO: Sound system?
 * TODO: unscuff the entity system?
 * TODO: Events?
 */

namespace Core {
    void Engine::Init(uint w, uint h) {
        SDL_Init(SDL_INIT_EVERYTHING);

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        TTF_Init();
        Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS);

        window = SDL_CreateWindow("osuX! - press the ovals", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
                                  SDL_WINDOW_HIDDEN);
        renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
        Mix_AllocateChannels(8);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        resourceManager = new ResourceManager();
        eventManager = new EventManager();

        eventManager->addEventListener(nullptr, SDL_QUIT, 100000, [](SDL_Event *e) {
            exit(0);
            return EventControl::HANDLED; //don't delete me
        });

        activeScene = new EntityCollection();

        atexit(Free);
    }

    void Engine::Free() {

        logher(INFO, "engine") << "Freeing resources..." << endlog;

        delete resourceManager;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    SDL_Window *Engine::getWindow() {
        return window;
    }

    SDL_Renderer *Engine::getRenderer() {
        return renderer;
    }

    [[noreturn]] void Engine::RunLoop() {

        SDL_ShowWindow(window);

        while (true) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                eventManager->dispatchEvent(&e);
            }

            activeScene->Render();

            SDL_RenderPresent(renderer);
            SDL_Delay(10); //scuffed fps limiter
        }
    }

}