//
//  TimeManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 14/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
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
    
    float deltaTime = 0.001;
    float elapsed = 0;
    std::chrono::steady_clock::time_point begin;
    clock_t dt;
    
    void start() {
        begin = std::chrono::steady_clock::now();
        elapsed = 0;
    }
    
    void update() {        
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
    }
    
    void startDelta() {
        dt = std::clock();
    }
    
    void delta() {
        deltaTime = (float)(std::clock() - dt) / CLOCKS_PER_SEC;
    }
    
};

#endif /* TimeManager_hpp */
