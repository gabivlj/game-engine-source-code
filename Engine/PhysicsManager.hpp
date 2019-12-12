//
//  PhysicsManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 14/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
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
class GameObjectManager;

class PhysicsManager : public Singleton<PhysicsManager> {
private:
    // Variables
    friend GameObjectManager;
    friend void nonGraphicsRelatedUpdate();
	friend StateManager;
    friend bool waitUntilUpdateFinishes();
	std::vector<GameObject*> gameObjects;
    
    // Methods
	void start(std::vector<GameObject*>* gosToSet) {
		// for loop copying to gameObjects array...
		for (int i = 0; i < gosToSet->size(); i++) {
			if ((*gosToSet)[i]->_collider != NONE) {
				gameObjects.push_back((*gosToSet)[i]);
			}
		}
	}
    
	void end() { gameObjects.clear(); };
    
	void update() {
		for (int i = 0; i < gameObjects.size(); i++) {
			for (int j = 0; j < gameObjects.size(); j++) {
                if (i == j) continue;
				AABBCollision(gameObjects[i], gameObjects[j]);
			}
		}
	};
    
	void popGameObject(GameObject* go) { 
		for (int i = 0; i < gameObjects.size(); i++) {
			if (go->instanceID() == gameObjects[i]->instanceID()) {
				gameObjects.erase(gameObjects.begin() + i);
				return;
			}
		}
	}

	// GABI TODO: AABBCollision should call onCollide() and pass gameObject there!!
	int AABBCollision(GameObject* self, GameObject* other) {
		vec2 selfCurrentPos = self->form.position;
		vec2 otherCurrentPos = other->form.position;

		int col = -1;
		ColFrom from = NOWHERE;
		if (self->form.position.y < other->form.position.y + other->form.dimension.height &&	// TOP
			self->form.position.x < other->form.position.x + other->form.dimension.width &&		// LEFT
			self->form.position.y + self->form.dimension.height > other->form.position.y &&		// BOTTOM
			self->form.position.x + self->form.dimension.width > other->form.position.x) {		// RIGHT
			// Calculate the side from where we collided
//       s     printf("1:%i, 2:%i\n", self->instanceID(), other->instanceID());
			float dists[4] = {
				std::abs((self->form.position.y) - (other->form.position.y + other->form.dimension.height)),	// TOP
				std::abs((self->form.position.x) - (other->form.position.x + other->form.dimension.width)),		// LEFT
				std::abs((self->form.position.y + self->form.dimension.height) - (other->form.position.y)),		// BOTTOM
				std::abs((self->form.position.x + self->form.dimension.width) - (other->form.position.x))		// RIGHT
			};
			// Get the minimum distance between opposites to know where we have collided from
			switch (min(dists, 4)) {
				case 0:
					from = ColFrom::C_TOP;
					break;
				case 1:
					from = ColFrom::C_LEFT;
					break;
				case 2:
					from = ColFrom::C_BOTTOM;
					break;
				case 3:
					from = ColFrom::C_RIGHT;
					break;
			}
			self->onCollide(other, &other->_collider, from);
		}
		// Return -1 if not collided, assigned integer if we did
        return col;
	}

	int min(float arr[], int size) {
		int min = HUGE_VALF;
		int pos = -1;
		for (int i = 0; i < size; i++) {
			if (arr[i] < min) {
				min = arr[i];
				pos = i;
			}
		}
		return pos;
	}
    
public:


};

#endif /* PhysicsManager_hpp */
