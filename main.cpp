///  PROJECT WITH SDL IN MAC/WINDOWS
///  Created by Gabriel Villalonga Simón and Daniel Gracia on 15/09/2019.
///  Copyright © 2019 Gabriel Villalonga Simón, Jorge SOlano Daniel Gracia. All rights reserved.
///
///  @@@@@@ This main is a test target for checking that all the libraries of this project work properly! @@@@@@
///             If Engine19 main.cpp is able to create the target, all is going right in your project configuration.
/// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/// @github: https://github.com/gabivlj/game-engine-source-code
#include <iostream>

#include "./Engine/Example/Square.hpp"

int main(int arg, char* args[]) {
    Scene* scene = new Scene();
    Dessert::Camera->setPosition(vec2{40, 40});
    Dessert::Camera->setSize(dimensions{1000, 1000});
    
    transform tr = transform{};
    tr.position = vec2{0, 0};
    tr.dimension.width = 100;
    tr.dimension.height = 100;
    // Sprite declaration
    const Sprite *sp = Dessert::Graphics->loadSprite("/loaded.png", dimensions{10, 10}, vec2{0, 0});
    
    tr.dimension.height += 100;
    tr.position.x += 150;
    GameObject* g2 = new GameObject(tr, "gm", sp);
    
    Game::Square* g3 = new Game::Square(tr, "gm", sp, 50);
    
    tr.position.x += 15;
    tr.position.y += 15;
    
    Game::Square* g4 = new Game::Square(tr, "gm2", sp, 50);
    tr.position.x += 15;
    tr.position.y += 15;
    
    Game::Square* g5 = new Game::Square(tr, "gm2", sp, 50);
    tr.position.x += 15;
    tr.position.y += 15;
    Game::Square* g = new Game::Square(tr, "gm", sp, 50);
    Scene* sc2 = new Scene();
    sc2->addObject(g);
    g->scene = scene;
    Game::Square* g6 = new Game::Square(tr, "gm2", sp, 50);
    tr.position.x += 15;
    tr.position.y += 15;
    Game::Square* g7 = new Game::Square(tr, "gm2", sp, 50);
    tr.position.x += 15;
    tr.position.y += 15;
    g3->scene = sc2;
    Game::Square* g8 = new Game::Square(tr, "gm2", sp, 50);
    tr.position.x += 15;
    tr.position.y += 15;
    Game::Square* g9 = new Game::Square(tr, "gm3", sp, 50);
    tr.position.x += 15;
    tr.position.y += 15;
    Game::Square* g10 = new Game::Square(tr, "gm3", sp, 50);
    tr.position.x += 15;
    tr.position.y += 15;
    
    Game::Square* g11 = new Game::Square(tr, "gm", sp, 50);

    // Object adding to scene
    tr.position.x += 115;
    tr.position.y += 55;
    GameObject* SQUARE = new GameObject(tr, "square");
    scene->addObject(SQUARE);
    scene->addObject(g11);
    scene->addObject(g10);
    scene->addObject(g9);
    scene->addObject(g8);
    scene->addObject(g7);
    scene->addObject(g6);
    scene->addObject(g5);
    scene->addObject(g4);
    scene->addObject(g3);
    scene->addObject(g2);
    Dessert::Scene->addScene(scene);
    Dessert::Scene->addScene(sc2);
    
        
    // Play game...
    Dessert::Scene->changeToScene(scene);
}
