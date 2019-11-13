//
//  StateManager.cpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 11/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#if __APPLE__
#include <SDL2/SDL.h>
#endif

#include "StateManager.hpp"
#include "Types/Scene.hpp"
#include "GameObjectManager.hpp"
#include "GraphicsManager.hpp"


void StateManager::start(Scene* scene) {
    if (playing) {
        // end();
    }
    playing = false;
    GameObjectManager::getInstance()->start(scene->_gameObjects, scene->nGameObjects);
    GraphicsManager::getInstance()->start();
    playing = true;
    update();
}

void StateManager::update() {
    while (playing) {
        // InputManager::start();
        GameObjectManager::getInstance()->update();
        // TODO: multithreading
        GraphicsManager::getInstance()->update(GameObjectManager::getInstance()->GetObjects(), GameObjectManager::getInstance()->GetObjects().size());
        
    }
}
