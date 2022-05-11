#include "BeatmapScene.hxx"

BeatmapScene::BeatmapScene(Beatmap *bm) {
    this->beatmap = bm;
    this->playMusic = true;
    //preload the music
    Engine::resourceManager->music->load("beatmap",beatmap->getAudioPath());

    this->playingField = new PlayingFieldEntity(bm);
    this->AddEntity(this->playingField);
}

void BeatmapScene::Render() {
    EntityCollection::Render();
}

void BeatmapScene::Activate() {
    this->AddEntity(new VolumeEntity());
    Mix_PlayMusic(Engine::resourceManager->music->get("beatmap"),0);
}
