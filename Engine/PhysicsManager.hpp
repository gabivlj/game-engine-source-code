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

#include "Singleton.hpp"
#include "Types/GameObject.hpp"

class StateManager;

class PhysicsManager : public Singleton<PhysicsManager> {
private:
	friend StateManager;
	std::vector<GameObject*> gameObjects;
	void start(std::vector<GameObject*>* gosToSet) { 
		// for loop copying to gameObjects array...
		for (int i = 0; i < gosToSet->size(); i++) {
//			if ((*gosToSet)[i]->_collider != NONE) {
//				gameObjects.push_back((*gosToSet)[i]);
//			}
		}
	}
	void end() { gameObjects.clear(); };
	void update() { }

	void AABBCollisiion(GameObject* self, GameObject* other) {

	}
public:


};

#endif /* PhysicsManager_hpp */
