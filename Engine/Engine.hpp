//
//  Engine.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 13/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include "GameObjectManager.hpp"
#include "GraphicsManager.hpp"
#include "SceneManager.hpp"
#include "InputManager.hpp"
#include "StateManager.hpp"
#include "./Types/Scene.hpp"


/**
 * @brief The game engine is called Dessert
 */
class Dessert {
public:
    
    static GameObjectManager* Game;
    static GraphicsManager* Graphics;
    static SceneManager* Scene;
    static InputManager* Input;
    static CameraManager* Camera;
    
    static void LoadComponent(DessertComponent* dessert) {
        StateManager::getInstance()->loadExternalsDessert(dessert);
    }
    
    Dessert() {
        
    }
};



//SceneManager *scenes = SceneManager::getInstance();
//GameObjectManager* gameObject = GameObjectManager::getInstance();
//GraphicsManager* graphics = GraphicsManager::getInstance();

#endif /* Engine_hpp */
