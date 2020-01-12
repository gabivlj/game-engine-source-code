//
//  Ship.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 12/01/2020.
//  Copyright © 2020 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

#include <stdio.h>
#include "../Types/GameObject.hpp"
#include "../Engine.hpp"

class Ship : public GameObject {
private:
    float speed = 100;
    
public:
    
    void move(const int vertical, const int horizontal, double dt) {
        form.position.x += (float) horizontal * speed * dt;
        form.position.y += (float) vertical * speed * dt;
    }
    
    void update(double deltaTime) override {
        InputManager input = *Dessert::Input;
        int inputs[4] = {input.getInput(UP), input.getInput(RIGHT), input.getInput(LEFT), input.getInput(DOWN)};
        if (inputs[0]) {
            setSpriteIndex(1);
        } else {
            setSpriteIndex(0);
        }        
        move(-inputs[0] + inputs[3], inputs[1] - inputs[2], deltaTime);
    }
    Ship(std::vector<const Sprite*> sprites) : GameObject(::transform {{50, 50}, {1, 1}, {24, 32}}, "yes", sprites, ColType::SQUARES) {};
    
};


#endif /* Ship_hpp */
