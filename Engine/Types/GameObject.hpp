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
#include "Collider.hpp"
#include "Sprite.hpp"

static int GLOBAL_ID = 0;


class PhysicsManager;
class GameObjectManager;
class GraphicsManager;

class GameObject {
private:
    
    friend PhysicsManager;
    friend GameObjectManager;
    friend GraphicsManager;
    
//    bool _endedFrame = false;
    
    ColType _collider;
    int _instanceID;
    std::string _tag;
    std::vector<const Sprite*> _sprites;
    int spriteIndex;
    // Current sprite.
    const Sprite* _sprite;
    bool instantiatedTest;
    transform _formRender;
    
public:
    // Variables
    transform form;
    
    bool _endedFrame = false;
    
    // Methods
    const int getInstanceID() {
        return _instanceID;
    }
    
    bool compareTag(const std::string t) {
        return t == _tag;
    }
    
    ~GameObject() {
        _sprites.clear();
        spriteIndex = 0;
        _sprite = 0x0;
        _tag = "";
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
    
    GameObject(::transform t, std::string tag) {
        instantiatedTest = tag == "prueba";
        form = t;
        _tag = tag;
        _sprites = std::vector<const Sprite*>();
        _sprite = 0;
//        setSpriteIndex(1);
        _instanceID = GLOBAL_ID++;
    }
    
    const Sprite* sprite() {
        
        return _sprite;
    }

    virtual void update(double deltaTime);
    
    virtual void start() {}
    
    void setCollider(ColType col) {
        _collider = col;
        // PhysicsManager::... -> informChange(this, col);
    }
    
    /**
     * @description Changes in shared pointers will be made at the end when no one is accessing it for sure.
     */
    void _end();
    
    void _update() {
    }
    
protected:

    void setSpriteIndex(int index) {
        spriteIndex = index;
    }
    
   
    
    virtual void onCollide(GameObject*, ColType*) {}
    
};

#endif /* GameObject_hpp */
