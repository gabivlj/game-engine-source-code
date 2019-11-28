//
//  PhysicsManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 14/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef PhysicsManager_hpp
#define PhysicsManager_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>

#include "Singleton.hpp"
#include "Types/GameObject.hpp"

class StateManager;

class PhysicsManager : public Singleton<PhysicsManager> {
private:
    // Variables
	friend StateManager;
    friend bool waitUntilUpdateFinishes();
    
	std::vector<GameObject*> gameObjects;
    
    // Methods
	void start(std::vector<GameObject*>* gosToSet) {
		// for loop copying to gameObjects array...
		for (int i = 0; i < gosToSet->size(); i++) {
			if ((*gosToSet)[i]->_collider.type != NONE) {
				gameObjects.push_back((*gosToSet)[i]);
			}
		}
	}
    
	void end() { gameObjects.clear(); };
    
	void update() { };
    
	void popGameObject(GameObject* go) { 
		for (int i = 0; i < gameObjects.size(); i++) {
			if (go == gameObjects[i]) {
				gameObjects.erase(gameObjects.begin() + i);
				return;
			}
		}
	}

	// GABI TODO: AABBCollision should call onCollide() and pass gameObject there!!
	bool AABBCollision(GameObject* self, GameObject* other) {
		if (self->form.position.y < other->form.position.y - other->form.dimension.height &&	// TOP
			self->form.position.x < other->form.position.x + other->form.dimension.width &&		// LEFT
			self->form.position.y + self->form.dimension.height < other->form.position.y &&		// BOTTOM
			self->form.position.x + self->form.dimension.width < other->form.position.x) {		// RIGHT
			// Calculate the side from where we collided
			float dists[] = {
				std::abs((self->form.position.y) - (other->form.position.y + other->form.dimension.height)),
				std::abs((self->form.position.x) - (other->form.position.x + other->form.dimension.width)),
				std::abs((self->form.position.y + self->form.dimension.height) - (other->form.position.y)),
				std::abs((self->form.position.x + self->form.dimension.width) - (other->form.position.x))
			};

			return true;
		}
        return false;
	}
    
public:


};

#endif /* PhysicsManager_hpp */
