#include "ScoreScene.hxx"

using namespace Entities;


void ScoreScene::Activate() {


    auto roboto = Engine::resourceManager->fonts->get("roboto");
    auto bounds = Engine::getPaintArea();

    this->bExit = new ButtonEntity(roboto,{bounds.w-100,44},{255,128,128,255},{255,0,0,255},"< Back", false);
    this->bExit->setHandler([]() {
        Engine::sceneManager->queueSceneSwitch(new MenuScene());
    });
    this->AddEntity(bExit);

    auto cy = bounds.h / 2 - 30;

    this->score = new TextEntity(roboto,{bounds.w/2,cy},{255,255,255,255},sscore, true);
    this->AddEntity(score);
    cy+=30;
    this->maxC = new TextEntity(roboto,{bounds.w/2,cy},{255,255,255,255},scombo, true);
    this->AddEntity(maxC);
    cy+=30;
    this->acc= new TextEntity(roboto,{bounds.w/2,cy},{255,255,255,255},sacc, true);
    this->AddEntity(acc);
}

ScoreScene::ScoreScene(int score, double acc, int maxCombo) {
    this->AddEntity(new WifeEntity());

    sscore = "Score: " + to_string(score);
    scombo = "Max combo: " + to_string(score);
    std::stringstream ss;
    ss << setprecision(4) << acc * 100 << " %";
    sacc = "Accuracy: " + ss.str();

    this->score = this->acc = this->maxC = nullptr;
    this->bExit = nullptr;
}
