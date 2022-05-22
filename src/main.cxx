#include <iostream>
#include <cstdio>

#include "include.hxx"
#include "IO/Beatmap.hxx"
#include "IO/Config.hxx"
#include "Textures.hxx"

#include "Core/Engine.hxx"
#include "Core/Scenes/Scene.hxx"
#include "Entities/Osu/PlayingFieldEntity.hxx"
#include "Entities/VolumeEntity.hxx"
#include "Scenes/BeatmapScene.hxx"
#include "Scenes/MenuScene.hxx"
#include "Core/Scenes/DefaultScene.hxx"
#include "IO/BeatmapCollection.hxx"

using namespace Core;

int main() {
    // enable colors on windows?
    IO::SetupLogging();

    //Load config and scan beatmaps
    Engine::LoadConf();
    IO::BeatmapCollection::scan();
    auto config = Engine::configManager->getConfig();

    //Initalize everything
    Engine::Init(config->hres, config->vres, config->fullscreen);

    //Preload textures
    for (const auto &p: textureList) { //load textures
        auto r = Engine::resourceManager->textures->load(p.first, p.second);
        if (r == nullptr) {
            logher(FATAL, "osux") << "Could not load texture: " << p.first << " from " << p.second << endlog;
            exit(0);
        }
    }

    // Earrape prevention
    Mix_VolumeMusic(40);

    auto intro = Engine::resourceManager->music->load("triangles","assets/triangles.mp3");
    Mix_PlayMusic(intro,0);

    logher(INFO, "osux") << "Initalization done; starting the main loop" << endlog;
    Engine::RunLoop(new DefaultScene(new MenuScene())); //Default scene = intro screen
}
