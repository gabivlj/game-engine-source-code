//
//  Collider.hpp
//  Engine19
//
//  Created by Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 14/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>
#include "Vector.hpp"


enum ColType {
	NONE = -1, SQUARES, CIRCLES, MIXED
};

enum ColFrom {
	NOWHERE = -1, C_TOP, C_LEFT, C_BOTTOM, C_RIGHT, C_DIRECTION
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
