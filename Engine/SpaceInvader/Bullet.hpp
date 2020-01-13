//
//  Bullet.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 13/01/2020.
//  Copyright © 2020 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "../Types/GameObject.hpp"
#include "../Engine.hpp"


class Bullet : public GameObject {
public:
    Bullet(vec2 position, const Sprite* spr) : GameObject({ position, {1, 1}, {5, 30} }, "bullet", spr) {
        
    }
    
    void start() override {
        printf("spawned lol");
    }
    
    void update(double dt) override {
//        form.position.y += -dt;
    }
private:
    
};

#endif /* Bullet_hpp */
