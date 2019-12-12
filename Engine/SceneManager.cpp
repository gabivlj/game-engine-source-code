//
//  SceneManager.cpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 13/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#include "SceneManager.hpp"
#include "StateManager.hpp"
#include "./Types/Scene.hpp"
#include <Windows.h>
// #include <unistd.h>

// sleep for this microseconds because the scene changing is REALLY fast (test).
unsigned int microseconds = 100000;

bool SceneManager::addScene(Scene* sceneToAdd) {
    scenes.push_back(sceneToAdd);
    return true;
}

bool SceneManager::changeToScene(Scene *sceneToChangeTo) {
    
    for (int i = 0; i < scenes.size(); ++i) {
       if (scenes[i] == sceneToChangeTo) {
           StateManager* stateManager = StateManager::getInstance();
           stateManager->nextScene = sceneToChangeTo;
           if (stateManager->playing) {
               Sleep(microseconds);
               stateManager->end();
           } else {
               stateManager->nextScene = NULL;
               stateManager->start(sceneToChangeTo);
           }
           return true;
       }
    }
   return false;
}

bool SceneManager::changeToScene(int index) {
    if (index < scenes.size()) {
        return true;
    }
    return false;
}
