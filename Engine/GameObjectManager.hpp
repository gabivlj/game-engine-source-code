//
//  GameObjectManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 13/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include <stdio.h>
#include <vector>
#include "Singleton.hpp"
#include "StateManager.hpp"
#include "Types/GameObject.hpp"


class GameObjectManager : public Singleton<GameObjectManager> {
private:
    
    std::vector<GameObject*> _objects;
    
    friend StateManager;
    
    bool start(GameObject** gameObjects, int len) {
        for (int i = 0; i < len; ++i) _objects.push_back(gameObjects[i]);
        return true;
    }
    
    void update() {
        
    }
    
public:
    std::vector<GameObject*> GetObjects() { return _objects; }
    
};

#endif /* GameObjectManager_hpp */