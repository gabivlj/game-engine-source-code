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
#include "TimeManager.hpp"

class StateManager;

enum TypeOfAction {
    INSTANTIATE, DELETE,
};

typedef struct {
    GameObject* gameObjectToApply;
    TypeOfAction action;
} Actions;

class GameObjectManager : public Singleton<GameObjectManager> {
private:
    
    std::vector<GameObject*> _objects;
    std::queue<Actions> _actions;
    
    friend StateManager;
    friend bool waitUntilUpdateFinishes();
    
    bool start(GameObject** gameObjects, int len) {
        for (int i = 0; i < len; ++i) _objects.push_back(gameObjects[i]);
        return true;
    }
    
    void update() {
        TimeManager* t = TimeManager::getInstance();
        for (GameObject* _object : _objects) {
            _object->update(t->deltaTime);
        }
        // Empty the queue
        while (!_actions.empty()) {
            Actions object = _actions.front();
            decideAction(&object);
            _actions.pop();
        }
    }
    
    void decideAction(Actions* action) {
        switch(action->action) {
            case TypeOfAction::INSTANTIATE:
                _objects.push_back(action->gameObjectToApply);
                return;
            case TypeOfAction::DELETE:
                for (int i = 0; i < _objects.size(); ++i)
                    if (_objects[i] == action->gameObjectToApply) {
                        _objects.erase(_objects.begin() + i);
                        return;
                    }
                std::cout << "Error on runtime: No object found on deleting...";
                return;
            default:
                return;
        }
    }
    
    void end() {
        _objects.clear();
    }
    
public:
    std::vector<GameObject*>* getObjects() { return &_objects; }
    
    GameObjectManager() {
        _actions = std::queue<Actions>();
    }
    
    bool Destroy(GameObject* gameObject) {
        _actions.push(Actions{gameObject, TypeOfAction::DELETE});
        return true;
    }
    
    bool Instantiate(GameObject* gameObject) {
        _actions.push(Actions{gameObject, TypeOfAction::INSTANTIATE});
//        _instantiated.push(gameObject);
        return true;
    }
    
};

#endif // GameObjectManager_hpp
