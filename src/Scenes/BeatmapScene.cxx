#include "BeatmapScene.hxx"

BeatmapScene::BeatmapScene(Beatmap *bm) {
    this->beatmap = bm;
    this->playMusic = true;
    //preload the music
    Engine::resourceManager->music->load(bm->getAudioPath(), beatmap->getAudioPath());

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

    auto roboto = Engine::resourceManager->fonts->load("roboto", "assets/roboto.ttf", 20);

    this->score = new Entities::TextEntity(roboto, {5, 5}, {255, 255, 255, 255}, "0", false);
    this->AddEntity(score);

    auto r = Engine::getPaintArea();
    this->acc = new Entities::TextEntity(roboto, {r.w - 90, 5}, {255, 255, 255, 255}, "", false);
    this->AddEntity(acc);

    this->combo = new Entities::TextEntity(roboto, {5, r.h-25}, {255, 255, 255, 255}, "0 x", false);
    this->AddEntity(combo);


    Mix_PlayMusic(Engine::resourceManager->music->get(beatmap->getAudioPath()), 0);
}

BeatmapScene::~BeatmapScene() {
    Mix_HaltMusic();
    SDL_ShowCursor(1);
}

void BeatmapScene::SetCombo(int c) {
    this->combo->setText(std::to_string(c) + " x");
}

void BeatmapScene::SetAcc(double a) {
    std::stringstream ss;
    ss << setprecision(4) << a *100 << " %";
    this->acc->setText(ss.str());
}

void BeatmapScene::SetScore(int s) {
    this->score->setText(std::to_string(s));
}
