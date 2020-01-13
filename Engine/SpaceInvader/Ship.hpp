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
#include "./Bullet.hpp"
#include <chrono>


class Ship : public GameObject {
private:
    float speed = 100;
    const Sprite* spriteBullet;
    bool canShoot = true;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
public:
    
    void move(const int vertical, const int horizontal, double dt) {
        form.position.x += (float) horizontal * speed * dt;
        form.position.y += (float) vertical * speed * dt;
    }
    
    float passedSeconds() {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
    }
    
    void restartTimer() {
        begin = std::chrono::steady_clock::now();
    }
    
    void handleShooting() {
        if (!canShoot && passedSeconds() > 0.0000000001f) {
            restartTimer();
            canShoot = true;
            return;
        }
        if (!canShoot) return;
        restartTimer();
        canShoot = false;
        std::cout << spriteBullet->path;
        Dessert::Game->Instantiate(new Bullet(form.position, spriteBullet));
    }
    
    void update(double deltaTime) override {
        InputManager input = *Dessert::Input;
        int inputs[5] = {input.getInput(UP), input.getInput(RIGHT), input.getInput(LEFT), input.getInput(DOWN), input.getInput(W_K)};
        if (inputs[0]) {
            setSpriteIndex(1);
        } else {
            setSpriteIndex(0);
        }        
        move(-inputs[0] + inputs[3], inputs[1] - inputs[2], deltaTime);
        if (inputs[4]) {
            handleShooting();
        }
    }
    
    Ship(std::vector<const Sprite*> sprites, const Sprite* bulletSpr) : GameObject(::transform {{50, 50}, {1, 1}, {24, 32}}, "yes", sprites, ColType::SQUARES) {
        spriteBullet = bulletSpr;
        restartTimer();
    };
    
    
    
};


#endif /* Ship_hpp */
