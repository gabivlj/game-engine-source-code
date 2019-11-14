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


void StateManager::start(Scene* scene) {
    playing = false;
    GameObjectManager::getInstance()->start(scene->_gameObjects, scene->nGameObjects);
    GraphicsManager::getInstance()->start();
    playing = true;
    update();
}

void graphicsThreadUpdate() {
    GraphicsManager::getInstance()->update(GameObjectManager::getInstance()->getObjects(), GameObjectManager::getInstance()->getObjects()->size());
}

void StateManager::update() {
    SDL_Event e;
    double frameRate = 60.0 / 1000.0;
    TimeManager* time = TimeManager::getInstance();
    int timesPlayed = 0;
    
    while(playing) {
        time->start();
        time->startDelta();
        while (SDL_PollEvent(&e)) {
            // InputManager::update();
        }
        
        std::thread graphicsThread(graphicsThreadUpdate);
        GameObjectManager::getInstance()->update();
        
        graphicsThread.join();
        
        while(TimeManager::getInstance()->elapsed < frameRate) {
            TimeManager::getInstance()->update();
        }
        time->delta();
        printf("elapsed: %f, %f\n", TimeManager::getInstance()->elapsed, frameRate);
        printf("times played: %i\n", timesPlayed);
        timesPlayed = 0;
        
    }
}

void StateManager::end() {
    GameObjectManager::getInstance()->end();
    GraphicsManager::getInstance()->end();
}
//
//SDL_Event e;
//bool quit = false;
//while (!quit){
//    while (SDL_PollEvent(&e)) {
//        InputManager* input = InputManager::createInstance();
//        bool up = input->GetAxis(ARROW_UP);
//        bool down = input->GetAxis(ARROW_DOWN);
//        if (e.type == SDL_QUIT){
//            quit = true;
//        }
//        w->clearWindow();
//        gm->y += (int)up * 10;
//        gm->y += (int)down * -10;
//
//        gm2->y += (int)up * 10;
//        gm2->y += (int)down * -10;
//        gm->update();
//        gm2->update();
//        w->UpdateWindow();
//    }
//}
//w->Destroy();
//SDL_Quit();
