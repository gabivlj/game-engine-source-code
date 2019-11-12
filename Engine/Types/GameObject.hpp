//
//  GameObject.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 17/10/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Sprite.hpp"

class GameObject {
private:
    static int GLOBAL_ID;
    int _instanceID;
    std::string _tag;
    std::vector<Sprite*> _sprites;
    // Current sprite.
    Sprite* _sprite;
    
public:
    // Variables
    transform transform;
    
    // Methods
    const int getInstanceID() {
        return _instanceID;
    }
    
    bool compareTag(const std::string t) {
        return t == _tag;
    }
    
    GameObject(::transform t, std::string tag) {
        transform = t;
        _tag = tag;
        _instanceID = GameObject::GLOBAL_ID++;
    }

protected:
    void setSpriteIndex(int index) {
        _sprite = _sprites[index];
    }
};

#endif /* GameObject_hpp */
