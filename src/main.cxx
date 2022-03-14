#include <iostream>
#include <cstdio>

#include "include.hxx"
#include "IO/Beatmap.hxx"
#include "Textures.hxx"

#include "Core/Engine.hxx"

#include "Entities/Osu/PlayingFieldEntity.hxx"
#include "Entities/VolumeEntity.hxx"

using namespace Core;

int main() {
    IO::SetupLogging();

    auto beatmap = new IO::Beatmap("/home/babnik/Downloads/freeze/fuckme.osu");

    Engine::Init(640, 480);


    for (const auto &p: textureList) {
        auto r = Engine::resourceManager->textures->load(p.first, p.second);
        if (r == nullptr) {
            logher(FATAL, "osux") << "Could not load texture: " << p.first << " from " << p.second << endlog;
            exit(0);
        }
    }

    Mix_VolumeMusic(5);

    auto playingField = new Osu::PlayingFieldEntity(beatmap);
    Engine::activeScene->AddEntity(new WifeEntity());
    Engine::activeScene->AddEntity(playingField);
    Engine::activeScene->AddEntity(new VolumeEntity());

    logher(INFO, "osux") << "Initalization done; starting the main loop" << endlog;


    auto m = Engine::resourceManager->music->load("beatmap_main", beatmap->getAudioPath());
    Mix_PlayMusic(m, 0);

    Engine::RunLoop();

    return 0;
}
