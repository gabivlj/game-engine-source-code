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
#include "./Enemy.hpp"
#include <chrono>

#include <iostream>
#include <random>

static std::random_device rd; // obtain a random number from hardware
static std::mt19937 eng(rd()); // seed the generator
static std::uniform_int_distribution<> randomRange(0, 400); // define the range 

class Ship : public GameObject {
private:
    float speed = 100;
    const Sprite* spriteBullet;
    const Sprite* spriteEnemy;
    bool canSpawn = true;
    bool canShoot = true;
    Scene* sceneToChangeTo;
    int goalDestroyedShips;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point beginEnemy = std::chrono::steady_clock::now();
    
public:
    
    void move(const int vertical, const int horizontal, double dt) {
        form.position.x += (float) horizontal * speed * dt;
        form.position.y += (float) vertical   * speed * dt;
    }
    
    float passedSeconds(std::chrono::steady_clock::time_point b) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(end - b).count();
    }
    
    void spawnEnemy() {
        if (!canSpawn && passedSeconds(beginEnemy) > 0.01f) {
            canSpawn = true;
        }
        if (!canSpawn) {
            return;
        }
        beginEnemy = std::chrono::steady_clock::now();;
        canSpawn = false;
        Dessert::Game->Instantiate(new Enemy(spriteEnemy, { (float) (randomRange(eng)), 0 }));
        Dessert::Game->Instantiate(new Enemy(spriteEnemy, { (float) (randomRange(eng)), 0 }));
        Dessert::Game->Instantiate(new Enemy(spriteEnemy, { (float) (randomRange(eng)), 0 }));
    }
    
    void restartTimer() {
        begin = std::chrono::steady_clock::now();
    }
    
    void handleShooting() {
        if (!canShoot && passedSeconds(begin) > 0.0000000001f) {
            restartTimer();
            canShoot = true;
            return;
        }
        if (!canShoot) return;
        restartTimer();
        canShoot = false;
        Dessert::Game->Instantiate(new Bullet(form.position, spriteBullet, &goalDestroyedShips));
    }
    
    void update(double deltaTime) override {
        InputManager input = *Dessert::Input;
        int inputs[5] = {
            input.getInput(UP),
            input.getInput(RIGHT),
            input.getInput(LEFT),
            input.getInput(DOWN),
            input.getInput(W_K)
        };
        if (inputs[0]) {
            setSpriteIndex(1);
        } else {
            setSpriteIndex(0);
        }        
        move(-inputs[0] + inputs[3], inputs[1] - inputs[2], deltaTime);
        if (inputs[4]) {
            handleShooting();
        }
        spawnEnemy();
        if (goalDestroyedShips <= 0) Dessert::Scene->changeToScene(sceneToChangeTo);
    }
    
    Ship(std::vector<const Sprite*> sprites, const Sprite* bulletSpr, const Sprite* enemySpr, Scene* scene, int goal)
    : GameObject(::transform { {50, 300}, {1, 1}, {24, 32} }, "player", sprites, ColType::SQUARES) {
        spriteBullet = bulletSpr;
        spriteEnemy = enemySpr;
        restartTimer();
        sceneToChangeTo = scene;
        goalDestroyedShips = goal;
    };
    
    
    
};


#endif /* Ship_hpp */
