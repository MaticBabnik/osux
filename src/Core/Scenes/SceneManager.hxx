#pragma once

#include "../../include.hxx"
#include "../Engine.hxx"
#include "Scene.hxx"
namespace Core::Scenes {

    //TODO: implement
    /*
     * A class that handles scene switching and state
     * Basically it needs to be a map with key:scene,
     * It also needs a function that switches scenes like sceneManager.switch("main");
     *
     * I also need to come up with a way to send state between scenes...
     * maybe with global maps of key:int, key:string and so on...
     *
     * It should also be able to show "new" scenes (without them being added to the map)
     */
    class SceneManager {
        //SwitchScene
        //Render(Top level render)
        // popup layer???
    };
}