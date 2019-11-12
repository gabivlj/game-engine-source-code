//
//  Sprite.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 17/10/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Sprite {
    std::string path;
public:
    Sprite(std::string p) {
        path = p;
    }
};

#endif /* Sprite_hpp */
