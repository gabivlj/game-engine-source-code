//
//  TimeManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 14/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef TimeManager_hpp
#define TimeManager_hpp

#include <stdio.h>
#include <ctime>
#include "Singleton.hpp"
#include <chrono>

class StateManager;
class GameObjectManager;

class TimeManager : public Singleton<TimeManager> {
public:
    TimeManager() {}
private:
    
    friend StateManager;
    friend GameObjectManager;
    friend void graphicsThreadUpdate();
    
    double deltaTime = 0.001;
    double elapsed = 0;
    double elapsedUpdate = 0;
    clock_t begin;
    clock_t dt;
    
    void start() {
        begin = std::clock();
        elapsed = 0;
        elapsedUpdate = 0;
    }
    
    void update() {        
        elapsed = (double)(std::clock() - begin ) / CLOCKS_PER_SEC ;
        elapsedUpdate = (double)(std::clock() - begin ) / CLOCKS_PER_SEC ;
    }
    
    void startDelta() {
        dt = std::clock();
    }
    
    void delta() {
        deltaTime = ((double)(std::clock() - dt) / CLOCKS_PER_SEC);
    }
    
};

#endif /* TimeManager_hpp */
