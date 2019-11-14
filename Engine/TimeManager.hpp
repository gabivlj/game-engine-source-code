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
    
    double deltaTime = 0.001;
    double elapsed = 0;
    clock_t begin;
    clock_t dt;
    
    void start() {
        begin = std::clock();
        elapsed = 0;
    }
    
    void update() {        
        elapsed = (double)(std::clock() - begin ) / CLOCKS_PER_SEC ;
    }
    
    void startDelta() {
        dt = std::clock();
    }
    
    void delta() {
        deltaTime = ((double)(std::clock() - dt) / CLOCKS_PER_SEC);
    }
    
};

#endif /* TimeManager_hpp */