//
//  Paddle.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 12/12/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include <stdio.h>
#include "../Engine.hpp"

class Paddle : public GameObject {
    float speed = 10;
    
public:
    Scene* scene;
    bool secondPlayer;
    Paddle(::transform t, std::string tag, float spd) : GameObject(t, tag, ColType::SQUARES) {
        speed = spd;
        secondPlayer = false;
    }
    
    Paddle(::transform t, std::string tag, float spd, bool p_secondPlayer) : GameObject(t, tag, ColType::SQUARES) {
        speed = spd;
        secondPlayer = p_secondPlayer;
    }
    
    void update(double dt) override {
        uint16_t intup = secondPlayer ? W_K : UP;
        uint16_t intdown = secondPlayer ? S_K : DOWN;
        key up = Dessert::Input->getInput(intup),
            down = Dessert::Input->getInput(intdown);
        
        float y = form.position.y;
        if (y < 0) {
            up = 0;
        }
        y += form.dimension.height;
        if (y > 1000) {
            down = 0;
        }
        form.position.y += speed * dt * (down - up);
    }
    
protected:
    void onCollide(GameObject *go, ColType* collider, ColFrom col) override {
    }
};


#endif /* Paddle_hpp */
