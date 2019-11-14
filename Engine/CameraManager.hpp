//
//  CameraManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 14/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef CameraManager_hpp
#define CameraManager_hpp

#include <stdio.h>
#include "./Singleton.hpp"
#include "Types/Vector.hpp"

class GraphicsManager;
class GameObject;
class StateManager;

class CameraManager : public Singleton<CameraManager>{
public:
    
    CameraManager() { }
    
    void setPosition(vec2 pos) {
        position = pos;
    }
    
    void setSize(dimensions newSize) {
        size = newSize;
    }
    
private:
    
    friend GraphicsManager;
    friend StateManager;
    friend GameObject;
    
    vec2 position;
    dimensions size;
    
    vec2 viewportPosition = {0, 0};
    dimensions viewportDimensions = {1000, 1000};
    
};

#endif /* CameraManager_hpp */
