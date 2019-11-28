//
//  Utils.hpp
//  Engine19
//
//  Created by Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 12/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#endif
#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif
#include <stdio.h>
#include "Vector.hpp"

class ConversionSDL {
public:
    /**
     * @param position position
     * @param dimension dimension
     * @description Position & dimension to SDL_Rect
     */
    static SDL_Rect* tosdlrect(vec2* position, dimensions* dimension) {
        SDL_Rect* rect = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 1);
        rect->x = position->x;
        rect->y = position->y;
        rect->w = dimension->width;
        rect->h = dimension->height;
        return rect;
    }
};

#endif /* Utils_hpp */
