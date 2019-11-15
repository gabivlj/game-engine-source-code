//
//  Collider.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 14/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>
#include "Vector.hpp"

enum ColliderType {
    NONE, AABB, CIRCULAR,
};


typedef struct {
    ColliderType type;
    transform collisioner;
    bool from[4] = { // TOP, LEFT, BOTTOM, RIGHT
        false,
        false,
        false,
        false};
} Collider;

#endif /* Collider_hpp */
