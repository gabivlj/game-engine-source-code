//
//  SceneManager.cpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 13/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#include "SceneManager.hpp"
#include "StateManager.hpp"
#include "./Types/Scene.hpp"

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
               stateManager->end();
           } else {
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
