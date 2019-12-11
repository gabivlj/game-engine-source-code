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
#include "../Engine.hpp"


namespace Game {

class Square : public GameObject {
    float speed = 10;
    
public:
    Scene* scene;
    Square(::transform t, std::string tag, const Sprite* sprite, float spd) : GameObject(t, tag, sprite) {
        speed = spd;
    }
    
    void update(double deltaTime) override {
        key esc = Dessert::Input->getInput(ESC_K);
        if (form.position.x > 300 || form.position.x < 0) {
            Dessert::Game->Destroy(this);
        }
        if (esc && scene) {
            Dessert::Scene->changeToScene(scene);
        }
        form.position.x += speed * deltaTime * (Dessert::Input->getInput(RIGHT) - Dessert::Input->getInput(LEFT));
        form.position.y += speed * deltaTime * (Dessert::Input->getInput(DOWN) - Dessert::Input->getInput(UP));
    }
    
protected:
    void onCollide(GameObject *go, ColType* collider) override {
    }
};

};

#endif /* Square_hpp */
