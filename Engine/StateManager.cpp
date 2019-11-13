//
//  StateManager.cpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 11/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#include "StateManager.hpp"
#include "Types/Scene.hpp"
#include "GameObjectManager.hpp"


void StateManager::start(Scene* scene) {
    playing = false;
    GameObjectManager::getInstance()->start(scene->_gameObjects, scene->nGameObjects);
}

