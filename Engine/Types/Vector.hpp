//
//  Vector.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 11/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>

typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    float width;
    float height;
} dimensions;

typedef struct {
    vec2 position;
	vec2 scale;
    dimensions dimension;
    float rotation;
} transform;


#endif /* Vector_hpp */
