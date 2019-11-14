////  PROJECT WITH SDL IN MAC/WINDOWS
////  Created by Gabriel Villalonga Simón and Daniel Gracia on 15/09/2019.
////  Copyright © 2019 Gabriel Villalonga Simón and Daniel Gracia. All rights reserved.
////
////  @@@@@@ This main is a test target for checking that all the libraries of this project work properly! @@@@@@
////      If Engine19 main.cpp is able to create the target, all is going right in your project configuration.
////  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <iostream>
#include "./Engine/Types/Scene.hpp"
#include "./Engine/Engine.hpp"
#include "./Engine/Example/Square.hpp"

int main(int arg, char* args[]) {
    GraphicsManager* graphics = GraphicsManager::getInstance();
    SceneManager* scenes = SceneManager::getInstance();
    
    CameraManager::getInstance()->setPosition(vec2{40, 40});
    CameraManager::getInstance()->setSize(dimensions{1000, 1000});
    
    Scene* scene = new Scene();
    transform tr = transform{};
    tr.position = vec2{0, 0};
    tr.dimension.width = 100;
    tr.dimension.height = 100;
    // Sprite declaration
    const Sprite *sp = graphics->loadSprite("/loaded.png", dimensions{10, 10}, vec2{0, 0});
    Square* g = new Square(tr, "gm", sp, 10);
    tr.dimension.height += 100;
    tr.position.x += 150;
    GameObject* g2 = new GameObject(tr, "gm", sp);
    // Object adding to scene
    scene->addObject(g);
    scene->addObject(g2);
    scenes->addScene(scene);
    // Play game
    scenes->changeToScene(scene);
    tr.dimension.height += 300;
    tr.position.x += 50;
    // Object adding to scene
}
