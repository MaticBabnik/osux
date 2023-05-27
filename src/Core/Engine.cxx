#include "Engine.hxx"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "./Scenes/DefaultScene.hxx"

namespace Core {

    constexpr auto noBitches = true; //haha very funny

    void Engine::Init(uint w, uint h, bool fullscreen) {
        SDL_Init(SDL_INIT_EVERYTHING);

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        TTF_Init();
        Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS);
        if (fullscreen) {

            SDL_DisplayMode dm;
            auto code = SDL_GetDesktopDisplayMode(0, &dm);
            if (code != 0) {
                logher(ERROR, "Engine") << "Couldn't get display mode: " << code << endlog;

                dm.w = w;
                dm.h = h;
            }
            window = SDL_CreateWindow("osuX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h,
                                      SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
        } else {
            window = SDL_CreateWindow("osuX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
        }
        renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
        Mix_AllocateChannels(16);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        resourceManager = new ResourceManager();
        sceneManager = new SceneManager(nullptr);

        slider_blend = SDL_ComposeCustomBlendMode(
                SDL_BLENDFACTOR_ZERO, //discard new color
                SDL_BLENDFACTOR_ONE, //keep src color
                SDL_BLENDOPERATION_ADD,
                SDL_BLENDFACTOR_ONE, //keep new alpha
                SDL_BLENDFACTOR_ZERO, //discard source alpha
                SDL_BLENDOPERATION_ADD
        );

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

        sceneManager->switchScene(firstScene);
        SDL_ShowWindow(window);

        while (noBitches) {
            sceneManager->switchSafePoint(); // switching scenes here _should_ not segfault

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
            SDL_Delay(5); //scuffed fps limiter
        }
    }

    SDL_Rect Engine::getPaintArea() {
        SDL_Rect r{-1, -1, 0, 0};
        SDL_GetWindowSize(getWindow(), &r.w, &r.h);

        return r;
    }

    SDL_BlendMode *Engine::getSliderBlend() {
        return &slider_blend;
    }

    void Engine::LoadConf() {
        configManager = new IO::Config();

        if (!configManager->load()) {
            logher(WARN, "osux") << "Could not read config" << endlog;
            if (!configManager->save()) {
                logher(ERROR, "osux") << "Could not read or write config... using default settings" << endlog;
            }
        }
    }

}