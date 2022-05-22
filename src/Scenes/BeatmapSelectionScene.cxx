#include "BeatmapSelectionScene.hxx"

using namespace std;
using namespace Entities;

const SDL_Color
        w = {255, 255, 255, 255},
        hl = {255, 100, 192, 255},
        g = {100, 255, 100, 255},
        r = {255, 100, 100, 255};


BeatmapSelectionScene::BeatmapSelectionScene() {
    this->bBeatmaps = new vector<ButtonEntity *>();
    this->AddEntity(new WifeEntity);
    this->selectedIndex = -1;
}

void BeatmapSelectionScene::Activate() {
    auto rTitle = Engine::resourceManager->fonts->load("rtitle", "assets/roboto.ttf", 30);
    auto roboto = Engine::resourceManager->fonts->get("roboto");
    auto bounds = Engine::getPaintArea();

    int cy = 5; // current Y, used to build the UI

    this->bExit = new ButtonEntity(roboto, {5, cy + 7}, r, hl, "< Back", false);
    bExit->forceRender(); // needed to get rect
    auto rExit = bExit->getRect();
    this->tPlay = new TextEntity(rTitle, {rExit.x + rExit.w + 20, cy}, w, "Beatmaps", false);
    tPlay->forceRender();
    auto rPlay = tPlay->getRect();
    this->bRefresh = new ButtonEntity(roboto, {rPlay.x + rPlay.w + 100, cy + 7}, g, hl, "refresh", false);

    this->bExit->setHandler([]() {
        Engine::sceneManager->queueSceneSwitch(new MenuScene());
    });
    this->bRefresh->setHandler([]() {
        IO::BeatmapCollection::scan();
        Engine::sceneManager->queueSceneSwitch(new BeatmapSelectionScene);
    });

    this->AddEntity(bExit);
    this->AddEntity(tPlay);
    this->AddEntity(bRefresh);

    cy += 30;
    cy += 20;

    auto beatmaps = IO::BeatmapCollection::getBeatmaps();
    {
        int i = 0;
        for (const auto &beatmap: *beatmaps) {
            auto b = new ButtonEntity(roboto, {20, cy}, w, hl, beatmap, false);
            cy += 25;
            this->bBeatmaps->push_back(b);
            this->AddEntity(b);

            b->setHandler([this,i]() {
                this->selectedIndex = i;
                this->tBigFilename->setText(IO::BeatmapCollection::getBeatmaps()->at(selectedIndex));
            });
            i++;
        }
    }

    auto rx = bounds.w - 400;
    this->AddEntity(new RectEntity({rx, 0, 400, bounds.h}, {0, 0, 0, 63}));

    cy = bounds.h / 2 - 30;
    this->tBigFilename = new TextEntity(roboto, {rx + 10, cy}, w, "No beatmap selected", false);
    this->AddEntity(tBigFilename);
    cy += 30;
    this->bPlay = new ButtonEntity(roboto, {rx + 10, cy}, g, w, "Play!", false);
    this->AddEntity(bPlay);
    cy += 30;

    this->bAutoPlay = new ButtonEntity(roboto, {rx + 10, cy}, g, w, "Autoplay", false);
    this->AddEntity(bAutoPlay);
    cy += 30;

    this->bPlay->setHandler([this]() {
        if (selectedIndex == -1) return;

        auto path = IO::BeatmapCollection::getBeatmaps()->at(selectedIndex);
        auto *scene = new BeatmapScene(new IO::Beatmap(path));
        Engine::sceneManager->queueSceneSwitch(scene);
    });

}