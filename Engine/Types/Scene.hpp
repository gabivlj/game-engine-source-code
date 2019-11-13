//
//  Scene.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 13/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "../Singleton.hpp"
#include "../StateManager.hpp"

class SceneManager;

class Scene {
private:
    GameObject** _gameObjects;
    friend StateManager;
    friend SceneManager;
public:
    int nGameObjects;
    /**
     * @param object GameObject to add.
     * @description Adds a gameObject to the list of gameObjects
     * @returns boolean, true if succesful, false otherwise.
     */
    bool addObject(GameObject* object) {
        _gameObjects = (GameObject**) realloc(_gameObjects, sizeof(GameObject*) * ++nGameObjects);
        _gameObjects[nGameObjects - 1] = object;
        return true;
    }
    
    Scene() { nGameObjects = 0; _gameObjects = (GameObject**) malloc(sizeof(GameObject*)); }
    
};

#endif /* Scene_hpp */
