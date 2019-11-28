//
//  GameObject.cpp
//  Engine19
//
//  Created by Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 17/10/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#include "GameObject.hpp"

#include "../GameObjectHelper.hpp"
#include "../GameObjectManager.hpp"


void GameObject::update(double deltaTime) {}

void GameObject::_end() {
    if (_sprites.size() && spriteIndex < _sprites.size()) {
        _sprite = _sprites[spriteIndex];
    }
    _formRender = form;    
    _endedFrame = true;
}

