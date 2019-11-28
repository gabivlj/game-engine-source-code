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

#include <thread>
#include "StateManager.hpp"
#include "Types/Scene.hpp"
#include "GameObjectManager.hpp"
#include "CameraManager.hpp"
#include "GraphicsManager.hpp"
#include "TimeManager.hpp"
#include "InputManager.hpp"
#include "PhysicsManager.hpp"


void StateManager::start(Scene* scene) {
    playing = false;
    finishedLoop = false;
    GameObjectManager::getInstance()->start(scene->_gameObjects, scene->nGameObjects);
    PhysicsManager::getInstance()->start(GameObjectManager::getInstance()->getObjects());
    GraphicsManager::getInstance()->start();
    playing = true;
    update();
}

void graphicsThreadUpdate() {
    int timesPlayed = 0;
    TimeManager* time = TimeManager::getInstance();
    
    while (StateManager::getInstance()->playing && !StateManager::getInstance()->finishedLoop) {
        time->startDelta();
        // Update every gameObject
        GameObjectManager::getInstance()->update();
        // Elapsed
        // Delta update
        time->delta();
        // Times played update
        timesPlayed = 0;
    }
}

void StateManager::update() {
    SDL_Event e;
    TimeManager* time = TimeManager::getInstance();
    // Start a new thread with every manager (Except the graphicsManager)
    std::thread graphicsThread(graphicsThreadUpdate);
    double frameRate = 30.0 / 1000.0;
    while (playing) {
        // Timing start
        time->start();
        
        // Poll event
        while (SDL_PollEvent(&e)) {
            InputManager::getInstance()->update(e);
        }
        TimeManager::getInstance()->start();
        GraphicsManager::getInstance()->update(
             GameObjectManager::getInstance()->getObjects(),
             (int) GameObjectManager::getInstance()->getObjects()->size()
        );
         while (TimeManager::getInstance()->elapsed < frameRate) {
                  TimeManager::getInstance()->update();
         }
        GameObjectManager::getInstance()->finish();
    }
    finishedLoop = true;
    graphicsThread.join();
}

bool waitUntilUpdateFinishes() {
    while (StateManager::getInstance()->finishedLoop) {}
    
    GameObjectManager::getInstance()->end();
    GraphicsManager::getInstance()->end();
    PhysicsManager::getInstance()->end();
    
    if (StateManager::getInstance()->nextScene) {
        StateManager::getInstance()->start(StateManager::getInstance()->nextScene);
    } else {
        // TODO: Exit app.
    }
    
    return true;
}

void StateManager::end() {
    playing = false;
    std::thread thread(waitUntilUpdateFinishes);
}
