#include "Engine.hxx"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "./Scenes/DefaultScene.hxx"
namespace Core {

    constexpr auto noBitches = true; //haha very funny

    void Engine::Init(uint w, uint h) {
        SDL_Init(SDL_INIT_EVERYTHING);

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        TTF_Init();
        Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS);

        window = SDL_CreateWindow("osuX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
                                  SDL_WINDOW_FULLSCREEN);
        renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
        Mix_AllocateChannels(8);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        resourceManager = new ResourceManager();
        sceneManager = new SceneManager(nullptr);


        atexit(Free);
    }

    void Engine::Free() {

        logher(INFO, "engine") << "Freeing resources..." << endlog;
        //TODO: fix SIGSEGV on exit don't know why ?
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

    [[noreturn]] void Engine::RunLoop(Scene *firstScene) {

        sceneManager->SwitchScene(firstScene);
        SDL_ShowWindow(window);

        while (noBitches) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                sceneManager
                        ->getActiveScene()
                        ->eventManager
                        ->dispatchEvent(&e);
            }

            sceneManager->getActiveScene()->Render();

            SDL_RenderPresent(renderer);
            SDL_Delay(10); //scuffed fps limiter
        }
    }

    SDL_Rect Engine::getPaintArea() {
        SDL_Rect r {-1,-1,0,0};
        SDL_GetWindowSize(getWindow(),&r.w,&r.h);

        return r;
    }

}