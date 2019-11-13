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
#include "Types/GameObject.hpp"

class StateManager;

class GameObjectManager : public Singleton<GameObjectManager> {
private:
    
    std::vector<GameObject*> _objects;
    
    friend StateManager;
    
    bool start(GameObject** gameObjects, int len) {
        for (int i = 0; i < len; ++i) _objects.push_back(gameObjects[i]);
        return true;
    }
    
    void update() {
        for (auto _object : _objects) {
            _object->update();
        }
    }
    
    void end() {
        _objects.clear();
    }
    
public:
    std::vector<GameObject*> getObjects() { return _objects; }
    
};

#endif // GameObjectManager_hpp
