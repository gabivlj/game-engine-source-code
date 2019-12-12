//
//  runnable.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 12/12/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef runnable_hpp
#define runnable_hpp

#include <stdio.h>
#include "../Engine.hpp"
#include "./Paddle.hpp"
#include "./Ball.hpp"

class Pong {
public:
    Pong() {
        vec2 position = {50, 500};
        vec2 scale = {1, 1};
        dimensions dim = {50, 100};
        transform paddlePosition1 = {position, scale, dim, 0};
        Paddle* paddle = new Paddle(paddlePosition1, "paddle1", 1000);
        paddlePosition1.position.x += 850;
        Paddle* paddle2 = new Paddle(paddlePosition1, "paddle2", 1000, true);
        Ball* b = new Ball();
        Scene* main = new Scene();
        main->addObject(b);
        main->addObject(paddle);
        main->addObject(paddle2);
        Dessert::Camera->setPosition(vec2{0, 0});
        Dessert::Camera->setSize(dimensions{1300, 1300});
        Dessert::Scene->addScene(main);
        Dessert::Scene->changeToScene(main);
    }
};

#endif /* runnable_hpp */
