#include "SettingsScene.hxx"


const SDL_Color w = {255, 255, 255, 255},
        hl = {255, 100, 192, 255},
        g = {100, 255, 100, 255},
        r = {255, 100, 100, 255};

void SettingsScene::Activate() {
    auto rTitle = Engine::resourceManager->fonts->load("rtitle", "assets/roboto.ttf", 30);
    auto roboto = Engine::resourceManager->fonts->get("roboto");

    int cy = 5; // current Y, used to build the UI

    // Title section
    // -----------------------------------------------------------------------------------------------------------------
    this->tTitle = new Entities::TextEntity(rTitle, {5, cy}, w, "Settings", false);
    this->AddEntity(tTitle);
    cy += 35;

    // Save Button
    // -----------------------------------------------------------------------------------------------------------------
    this->bSave = new ButtonEntity(roboto, {10, cy}, g, hl, "Save", false);
    this->bSave->setHandler([this]() {
        memcpy(Engine::configManager->getConfig(), &ocfg, sizeof(IO::OsuxConfig));
        if (!Engine::configManager->save()) {
            logher(ERROR, "SettingsScene") << "Could not write config." << endlog;
        }
        Engine::sceneManager->queueSceneSwitch(new MenuScene());
    });
    this->AddEntity(bSave);

    // Exit Button
    // -----------------------------------------------------------------------------------------------------------------
    this->bExit = new ButtonEntity(roboto, {90, cy}, r, hl, "Exit", false);
    this->bExit->setHandler([]() {
        Engine::sceneManager->queueSceneSwitch(new MenuScene());
    });
    this->AddEntity(bExit);

    cy += 25;

    // Fullscreen toggle
    // -----------------------------------------------------------------------------------------------------------------
    this->bFullscreen = new ButtonEntity(roboto, {10, cy}, w, hl,
                                         (string) "Fullscreen: " + (ocfg.fullscreen ? "YES" : "NO"), false);
    bFullscreen->setHandler([this]() {
        ocfg.fullscreen = !ocfg.fullscreen;
        bFullscreen->setText((string) "Fullscreen: " + (ocfg.fullscreen ? "YES" : "NO"));
    });

    this->AddEntity(bFullscreen);

    cy += 30;

    // Resolution list
    // -----------------------------------------------------------------------------------------------------------------
    this->tResolution = new Entities::TextEntity(roboto, {10, cy}, w, "Resolution: ", false);
    this->AddEntity(tResolution);

    cy += 25;

    for (int i = 0; i < n_res; i++) {
        auto p = resolutions[i];

        string label;
        if (ocfg.hres == resolutions[i].x && ocfg.vres == resolutions[i].y) {
            label = "> " + to_string(p.x) + "x" + to_string(p.y);
        } else {
            label = to_string(p.x) + "x" + to_string(p.y);
        }

        if (p.x==1080) {
            /*
             * David& — Today at 5:36 PM
             * kaj pa 1080x1920?
             * (za mobile userje)
             */
            label += " (David Studen edition)";
        }

        auto r = new ButtonEntity(roboto, {20, cy}, w, hl, label, false);
        r->setHandler([this,i] () {
            ocfg.hres = resolutions[i].x;
            ocfg.vres = resolutions[i].y;

            for (int i = 0; i < n_res; i++) {
                auto p = resolutions[i];

                string label;
                if (ocfg.hres == resolutions[i].x && ocfg.vres == resolutions[i].y) {
                    label = "> " + to_string(p.x) + "x" + to_string(p.y);
                } else {
                    label = to_string(p.x) + "x" + to_string(p.y);
                }
                if (p.x==1080) {
                    label += " (David Studen edition)";
                }

                auto rbtn = (*this->bResolutions)[i];
                rbtn->setText(label);
            }
        });

        this->bResolutions->push_back(r);
        this->AddEntity(r);
        cy += 25;
    }
    cy += 15;

    // Restart warning
    // -----------------------------------------------------------------------------------------------------------------
    this->tRestart = new Entities::TextEntity(roboto, {5, cy}, hl, "Game needs to be restarted in order to apply.", false);
    this->AddEntity(tRestart);
    cy += 35;

}

SettingsScene::SettingsScene(IO::Config *cfg) {
    this->AddEntity(new WifeEntity);
    this->bResolutions = new vector<ButtonEntity *>();
    //make a copy of the config
    memcpy(&this->ocfg, cfg->getConfig(), sizeof(IO::OsuxConfig));
}
