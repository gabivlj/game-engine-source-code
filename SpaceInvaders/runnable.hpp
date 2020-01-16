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
#include "../Engine/Engine.hpp"
#include "../Externals/SoundManager.hpp"
#include "Ship.hpp"

class ShipInvaders {
public:
    ShipInvaders() {
        // Load our own External Component into the engine (So it gets started, updated and finished.)
        Dessert::LoadComponent(&soundManager);
        // Load sound into soundManager
        Sound* laser = soundManager.loadSound("assets/laser.wav");
        Sound* music = soundManager.loadMusic("assets/soundtrack.wav");        
        // Load sprites
        const Sprite* bullet = Dessert::Graphics->loadSprite("assets/bullet.png", {5, 30}, {0, 0});
        const Sprite* enemySpr = Dessert::Graphics->loadSprite("assets/enemy.png", {30, 30}, {0, 0});
        const Sprite* ship01 = Dessert::Graphics->loadSprite("assets/ship01.png", {16, 24}, {0, 0});
        const Sprite* ship02 = Dessert::Graphics->loadSprite("assets/ship02.png", {16, 24}, {0, 0});
        const Sprite* background = Dessert::Graphics->loadSprite("assets/background.png", {1000, 1000}, {0, 0});
        std::vector<const Sprite*> spritesShip;
        spritesShip.push_back(ship01);
        spritesShip.push_back(ship02);

        // Background
        GameObject* bck = new GameObject({vec2{0, 0}, vec2{1, 1}, {1000, 1000}}, "background", background);
        Scene* main = new Scene();
        Scene* second = new Scene();
        
        Ship* ship = new Ship(spritesShip, bullet, enemySpr, second, 3, laser, music);
        Ship* shipScene2 = new Ship(spritesShip, bullet, enemySpr, main, 3, laser, music);
        main->addObject(bck);
        main->addObject(ship);
        second->addObject(bck);
        second->addObject(shipScene2);        
        Dessert::Camera->setPosition(vec2{0, 0});
        Dessert::Camera->setSize(dimensions{400, 400});
        Dessert::Scene->addScene(main);
        Dessert::Scene->addScene(second);
        Dessert::Scene->changeToScene(main);
    }
};

#endif /* runnable_hpp */
