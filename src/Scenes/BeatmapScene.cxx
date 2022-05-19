#include "BeatmapScene.hxx"

BeatmapScene::BeatmapScene(Beatmap *bm) {
    this->beatmap = bm;
    this->playMusic = true;
    //preload the music
    Engine::resourceManager->music->load("beatmap", beatmap->getAudioPath());


}

void BeatmapScene::Render() {
    auto r = Engine::getRenderer();

    int x, y;
    SDL_GetMouseState(&x, &y);

    const SDL_Rect rect = {x - 12, y - 12, 24, 24};

    EntityCollection::Render();
    SDL_RenderCopy(r, Engine::resourceManager->textures->getRawTexture("cursor"), nullptr, &rect);
}

void BeatmapScene::Activate() {
    this->AddEntity(new WifeEntity());

    SDL_ShowCursor(0);

    this->playingField = new PlayingFieldEntity(this->beatmap);
    this->AddEntity(this->playingField);
    this->AddEntity(new VolumeEntity());

    Mix_PlayMusic(Engine::resourceManager->music->get("beatmap"), 0);
}
