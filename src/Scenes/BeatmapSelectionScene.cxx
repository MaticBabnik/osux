#include "BeatmapSelectionScene.hxx"

using namespace std;
using namespace Entities;

const SDL_Color w = {255, 255, 255, 255},
                hl = {255, 100, 192, 255},
                g = {100, 255, 100, 255},
                r = {255, 100, 100, 255};


BeatmapSelectionScene::BeatmapSelectionScene() {
   this->bBeatmaps =  new vector<ButtonEntity*>() ;
   this->AddEntity(new WifeEntity);
}

void BeatmapSelectionScene::Activate() {
    auto rTitle = Engine::resourceManager->fonts->load("rtitle", "assets/roboto.ttf", 30);
    auto roboto = Engine::resourceManager->fonts->get("roboto");

    int cy = 5; // current Y, used to build the UI

    this->bExit =    new ButtonEntity(roboto,{5,cy+5},r,hl,"< Back");
    auto rExit = bExit->getRect();
    this->tPlay =    new TextEntity(rTitle,{5+rExit.w+20,cy},w,"Beatmaps",false);
    auto rPlay = bPlay->getRect();
    this->bRefresh = new ButtonEntity(roboto,{5+rPlay.x+rPlay.w,cy+5},g,hl,"refresh");

    this->AddEntity(bExit);
    this->AddEntity(tPlay);
    this->AddEntity(bRefresh);


//    this->bPlay;
//    this->bAutoPlay;
//    this->tBigFilename;
}
