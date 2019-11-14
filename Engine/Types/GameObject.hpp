//
//  GameObject.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 17/10/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Sprite.hpp"

static int GLOBAL_ID = 0;

enum ColliderType {
    NONE, AABB, CIRCULAR,
};

enum From {
	TOP, LEFT, BOTTOM, RIGHT
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

class PhysicsManager;
class GameObjectManager;

class GameObject {
private:
    
    friend PhysicsManager;
    friend GameObjectManager;
    
    Collider _collider;
    int _instanceID;
    std::string _tag;
    std::vector<const Sprite*> _sprites;
    // Current sprite.
    const Sprite* _sprite;
    bool instantiatedTest;
public:
    // Variables
    transform form;
    
    // Methods
    const int getInstanceID() {
        return _instanceID;
    }
    
    bool compareTag(const std::string t) {
        return t == _tag;
    }
    
    GameObject(::transform t, std::string tag, const Sprite* sprite) {
        instantiatedTest = tag == "prueba";        
        form = t;
        _tag = tag;
        _sprites = std::vector<const Sprite*>();
        _sprites.push_back(sprite);
        setSpriteIndex(0);
        _instanceID = GLOBAL_ID++;
    }
    
    const Sprite* sprite() {
        return _sprite;
    }

    virtual void update();
    
    void setCollider(Collider col) {
        _collider = col;
        // PhysicsManager::... -> informChange(this, col);
    }
    
protected:
    void setSpriteIndex(int index) {
        _sprite = _sprites[index];
    }
    
};

#endif /* GameObject_hpp */
