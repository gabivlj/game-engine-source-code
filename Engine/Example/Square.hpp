//
//  Square.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 14/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>
#include "../CameraManager.hpp"
#include "../WindowManager.hpp"
#include "../Types/GameObject.hpp"

class Square : public GameObject {
    float speed = 10;
public:
    Square(::transform t, std::string tag, const Sprite* sprite, float spd) : GameObject(t, tag, sprite) {
        speed = spd;
    }
    
    void update(double deltaTime) override {
        if (form.position.x > 50 || form.position.x < 0) {
            speed *= -1;
        }
        form.position.x += speed;
//        WindowManager* w = WindowManager::getInstance();
//        vec2 sizes = vec2{(static_cast<float>(w->SCREEN_W/2)), static_cast<float>((w->SCREEN_H/2))};
//        CameraManager::getInstance()->setPosition(vec2{ form.position.x - sizes.x, form.position.y - sizes.y});
    }
    
protected:
    void onCollide(GameObject *go, Collider* collider) override {
    }
};

#endif /* Square_hpp */
