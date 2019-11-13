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
#include <stack>
#include <queue>
#include "Singleton.hpp"
#include "Types/GameObject.hpp"

class StateManager;

class GameObjectManager : public Singleton<GameObjectManager> {
private:
    
    std::vector<GameObject*> _objects;
    std::queue<GameObject*> _instantiated;
    
    friend StateManager;
    
    bool start(GameObject** gameObjects, int len) {
        for (int i = 0; i < len; ++i) _objects.push_back(gameObjects[i]);
        return true;
    }
    
    void update() {
        for (GameObject* _object : _objects) {
            _object->update();
        }
        // Empty the queue
        while (!_instantiated.empty()) {
            printf("%i\n", _instantiated.size());
            _objects.push_back(_instantiated.front());
            _instantiated.pop();
        }
    }
    
    void end() {
        _objects.clear();
    }
    
public:
    std::vector<GameObject*>* getObjects() { return &_objects; }
    
    GameObjectManager() {
        _objects = std::vector<GameObject*>();
        _instantiated = std::queue<GameObject*>();
    }
    
    bool Instantiate(GameObject* gameObject) {
        _instantiated.push(gameObject);
        return true;
    }
    
};

#endif // GameObjectManager_hpp
