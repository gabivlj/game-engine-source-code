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

enum Collider {
    NONE, SQUARE, CIRCULAR,
};

enum ColType {
	NONE = -1, SQUARES, CIRCLES, MIXED
};

enum ColFrom {
	NOWHERE = -1, TOP, LEFT, BOTTOM, RIGHT, DIRECTION
};


// typedef struct {
//     Collider type;
//     transform collisioner;
//     bool from[4] = { // TOP, LEFT, BOTTOM, RIGHT
//         false,
//         false,
//         false,
//         false};
// } Collider;

typedef struct {
	ColType type;
	ColFrom from;
} Collision;

#endif /* Collider_hpp */
