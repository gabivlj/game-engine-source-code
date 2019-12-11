//
//  Sprite.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 17/10/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#endif
#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif



class Sprite {
    std::string path;
public:
    Sprite(std::string p) {
        path = p;
    }
};

#endif /* Sprite_hpp */
