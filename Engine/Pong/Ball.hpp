//
//  Ball.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 12/12/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "../Engine.hpp"

class Ball : public GameObject {
    float speed = 1000;
    float signX = 1.0f;
    float signY = 1.0f;
    
public:
    
    Ball() : GameObject(transform{vec2{500 - 50, 500 - 50}, vec2{1,1}, dimensions{50, 50}, 0}, "ball") {
        speed = 500;
        printf("%f, %f", form.dimension.width, form.position.y);
        
    }
    
    void update(double dt) override {
        float x = form.position.x + 50;
        float y = form.position.y;

        if (x >= 1000) {
            signX = -1.0f;
        } else if (x - 50 < 0) {
            signX = 1.0f;
        }
        
        if (y + 50 > 1000) {
            signY = -1.0f;
        }
        
        if (y < 0) {
            signY = 1.0f;
        }
        
        form.position.x += signX * speed * dt;
        form.position.y += signY * (speed + 10) * dt;
        
    }
    
protected:
    void onCollide(GameObject *go, ColType* collider) override {
    }
};
#endif /* Ball_hpp */
