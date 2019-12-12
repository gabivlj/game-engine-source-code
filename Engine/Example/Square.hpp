//
//  Square.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 14/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>
#include "../GameObjectManager.hpp"
#include "../CameraManager.hpp"
#include "../InputManager.hpp"
#include "../WindowManager.hpp"
#include "../Types/GameObject.hpp"
#include "../GameObjectHelper.hpp"
#include "../SceneManager.hpp"
#include "../Types/Scene.hpp"



class Square : public GameObject {
    float speed = 10;
    InputManager* input;
    
public:
    Scene* scene;
    Square(::transform t, std::string tag, const Sprite* sprite, float spd) : GameObject(t, tag, sprite) {
        speed = spd;
        input = InputManager::getInstance();
    }
    
    void update(double deltaTime) override {
        key esc = input->getInput(ESC_K);
        if (form.position.x > 300 || form.position.x < 0) {
            GameObjectManager::getInstance()->Destroy(this);
        }
        if (esc && scene) {
            printf("xD");
            printf("%i", scene);
            SceneManager::getInstance()->changeToScene(scene);
        }
        form.position.x += speed * deltaTime * (input->getInput(RIGHT) - input->getInput(LEFT));
        form.position.y += speed * deltaTime * (input->getInput(DOWN) - input->getInput(UP));
    }
    
protected:
    void onCollide(GameObject *go, ColType* collider) override {
    }
};

#endif /* Square_hpp */
