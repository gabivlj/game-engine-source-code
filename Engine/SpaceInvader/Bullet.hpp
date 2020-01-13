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
    int* leftBullets;
public:
    
    Bullet(vec2 position, const Sprite* spr, int* left) : GameObject({ position, {1, 1}, {5, 30} }, "bullet", spr, ColType::SQUARES) {
        leftBullets = left;
    }
    
    void start() override {}
    
    void onCollide(GameObject* col , ColType* t, ColFrom from) override {
        if (from == ColFrom::C_TOP) {
            Dessert::Game->Destroy(col);
            (*leftBullets)--;
        }
    }
    
    void update(double dt) override {
        form.position.y += -dt * 200;
        if (form.position.y < 0) {
            Dessert::Game->Destroy(this);
        }
    }
private:
    
};

#endif /* Bullet_hpp */
