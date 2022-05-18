#include <iostream>
#include <cstdio>

#include "include.hxx"
#include "IO/Beatmap.hxx"
#include "Textures.hxx"

#include "Core/Engine.hxx"
#include "Core/Scenes/Scene.hxx"
#include "Entities/Osu/PlayingFieldEntity.hxx"
#include "Entities/VolumeEntity.hxx"
#include "Scenes/BeatmapScene.hxx"
#include "Scenes/SliderTestScene.hxx"
#include "Scenes/MenuScene.hxx"
#include "Core/Scenes/DefaultScene.hxx"

using namespace Core;

int main() {
    IO::SetupLogging();

    auto beatmap = new IO::Beatmap("assets/test/main.osu");

    Engine::Init(640, 480, false);


    for (const auto &p: textureList) { //load textures
        auto r = Engine::resourceManager->textures->load(p.first, p.second);
        if (r == nullptr) {
            logher(FATAL, "osux") << "Could not load texture: " << p.first << " from " << p.second << endlog;
            exit(0);
        }
    }

    Mix_VolumeMusic(40);

    logher(INFO, "osux") << "Initalization done; starting the main loop" << endlog;
    auto n = new BeatmapScene(beatmap);
    //auto krogi = Engine::resourceManager->music->load("circles","assets/nekodex-circles.mp3");
    //Mix_PlayMusic(krogi,0);

    //new MenuScene()
    Engine::RunLoop(new DefaultScene(n));

    return 0;
}
