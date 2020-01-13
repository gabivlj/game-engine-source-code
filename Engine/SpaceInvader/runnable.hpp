//
//  runnable.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 12/01/2020.
//  Copyright © 2020 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef runnable_hpp
#define runnable_hpp

#include <stdio.h>
#include <vector>
#include "../Engine.hpp"
#include "Ship.hpp"

class ShipInvaders {
public:
    ShipInvaders() {
        const Sprite* bullet = Dessert::Graphics->loadSprite("assets/bullet.png", {5, 30}, {0, 0});
        const Sprite* enemySpr = Dessert::Graphics->loadSprite("assets/enemy.png", {30, 30}, {0, 0});
        const Sprite* ship01 = Dessert::Graphics->loadSprite("ship01.png", {16, 24}, {0, 0});
        const Sprite* ship02 = Dessert::Graphics->loadSprite("ship02.png", {16, 24}, {0, 0});
        const Sprite* background = Dessert::Graphics->loadSprite("assets/background.png", {1000, 1000}, {0, 0});
        std::vector<const Sprite*> spritesShip;
        spritesShip.push_back(ship01);
        spritesShip.push_back(ship02);
        // Background
        GameObject* bck = new GameObject({vec2{0, 0}, vec2{1, 1}, {1000, 1000}}, "background", background);
        Scene* main = new Scene();
        Ship* ship = new Ship(spritesShip, bullet, enemySpr);
        main->addObject(bck);
        main->addObject(ship);
        Dessert::Camera->setPosition(vec2{0, 0});
        Dessert::Camera->setSize(dimensions{400, 400});
        Dessert::Scene->addScene(main);
        Dessert::Scene->changeToScene(main);
    }
};

#endif /* runnable_hpp */
