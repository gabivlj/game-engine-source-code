//
//  StateManager.cpp
//  Engine19
//
//  Created by Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 11/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifdef _WIN32
#include <SDL.h>
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
#include "SceneManager.hpp"
#include "PhysicsManager.hpp"


void StateManager::start(Scene* scene) {
    playing = false;
    finishedLoop = false;
    ended = false;
    GameObjectManager::getInstance()->start(scene->_gameObjects, scene->nGameObjects);
    PhysicsManager::getInstance()->start(GameObjectManager::getInstance()->getObjects());
    GraphicsManager::getInstance()->start();
    playing = true;
    update();
}

void nonGraphicsRelatedUpdate() {
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

/**
 * @brief Update lifecycle of the engine
 * @discussion The update lifecycle of the entire application, basically spawns another thread for all of the non-related graphic stuff and then uses the main thread to run the GraphicsManager update so there ain't compatibility issues with Windows and no buggy bugs.
 */
void StateManager::update() {
    SDL_Event e;
    TimeManager* time = TimeManager::getInstance();
    // Start a new thread with every manager (Except the graphicsManager)
    std::thread graphicsThread(nonGraphicsRelatedUpdate);
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
    printf("se salio way");
    GameObjectManager::getInstance()->end();
    PhysicsManager::getInstance()->end();
    if (StateManager::getInstance()->nextScene != NULL) {
        printf("xd");
        StateManager::getInstance()->start(StateManager::getInstance()->nextScene);
    } else {
            printf("end");
           GraphicsManager::getInstance()->end();
    }

    ended = true;
}

/**
 * @discussion Tries to end the application
 */
bool waitUntilUpdateFinishes() {
    

    
    return true;
}

void StateManager::end() {
    playing = false;
    printf("END\n");
//    std::thread thread(waitUntilUpdateFinishes);
   
}

