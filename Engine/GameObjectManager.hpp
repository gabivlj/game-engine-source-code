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
#include "GraphicsManager.hpp"

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
    
    friend void graphicsThreadUpdate();
    friend StateManager;
    friend bool waitUntilUpdateFinishes();
    
    
    bool start(GameObject** gameObjects, int len) {
        for (int i = 0; i < len; ++i) { _objects.push_back(gameObjects[i]); gameObjects[i]->start(); gameObjects[i]->_end(); }
        return true;
    }
    
    void update() {
        TimeManager* t = TimeManager::getInstance();
        for (GameObject* _object : _objects) {
            _object->update(t->deltaTime);
            _object->_update();
        }
        // Empty the queue
        while (!_actions.empty()) {
            Actions object = _actions.front();
            decideAction(&object);
            _actions.pop();
        }
    }
    
    /**
     * @summary When finishing a frame rendering, this will execute save actions on shared thread pointers on each GameObject.
     */
    void finish() {
        for (int i = 0; i < _objects.size(); ++i) { _objects[i]->_end(); }
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
        // empty queue if there are actions left.
        if (!_actions.empty()) {
            std::queue<Actions> empty;
            std::swap(_actions, empty);
        }
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
        return true;
    }
    
//    void drawLine(vec2 point1, vec2 point2) {
//        GraphicsManager::getInstance()->drawLine(point1, point2);
//    }
    
};

#endif // GameObjectManager_hpp
