//
//  Enemy.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 13/01/2020.
//  Copyright © 2020 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "../Types/GameObject.hpp"
#include "../Engine.hpp"
#include "./Bullet.hpp"
#include <chrono>


class Enemy : public GameObject {
private:
    float speed = 100;
    
public:
    
    void move(const int vertical, const int horizontal, double dt) {
        form.position.x += (float) horizontal * speed * dt;
        form.position.y += (float) vertical   * speed * dt;
    }
    
    
    void update(double deltaTime) override {
        move(1, 0, deltaTime);
        if (form.position.y > 400) {
            Dessert::Game->Destroy(this);
        }
    }
    
    Enemy(const Sprite* sprite, vec2 pos) : GameObject(::transform { pos, {1, 1}, {24, 32} }, "enemy", sprite, ColType::SQUARES) {
    };
    
    void onCollide(GameObject * g, ColType *c, ColFrom f) override {
        if (g->compareTag("player")) {
            Dessert::Game->Destroy(g);
        }
    }
    
};


#endif /* Enemy_hpp */
