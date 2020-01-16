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
    /**
     * @brief Transform of the object.
     */
    transform form;
    
    bool _endedFrame = false;
    
    /**
     * @brief The unique instance ID
     */
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
    
    GameObject(::transform t, std::string tag, ColType col) {
        instantiatedTest = tag == "prueba";
        form = t;
        _tag = tag;
        _sprites = std::vector<const Sprite*>();
        _sprite = 0;
        _instanceID = GLOBAL_ID++;
        _collider = col;
    }
    
    GameObject(::transform t, std::string tag, const Sprite* sprite) {
        instantiatedTest = tag == "prueba";        
        form = t;
        _tag = tag;
        _sprites = std::vector<const Sprite*>();
        _sprites.push_back(sprite);
        setSpriteIndex(0);
        _instanceID = GLOBAL_ID++;
        _collider = ColType::NONE;
    }
    
    GameObject(::transform t, std::string tag, std::vector<const Sprite*> sprites, ColType col) {
        instantiatedTest = tag == "prueba";
        form = t;
        _tag = tag;
        _sprites = sprites;
        setSpriteIndex(0);
        _instanceID = GLOBAL_ID++;
        _collider = col;
    }
    
    GameObject(::transform t, std::string tag, const Sprite* sprite, ColType col) {
        instantiatedTest = tag == "prueba";
        form = t;
        _tag = tag;
        _sprites = std::vector<const Sprite*>();
        _sprites.push_back(sprite);
        setSpriteIndex(0);
        _instanceID = GLOBAL_ID++;
        _collider = col;
    }
    
    GameObject(::transform t, std::string tag) {
        instantiatedTest = tag == "prueba";
        form = t;
        _tag = tag;
        _sprites = std::vector<const Sprite*>();
        _sprite = 0;
        _collider = ColType::NONE;
        _instanceID = GLOBAL_ID++;
    }
    
    /**
     * @return Current sprite
     */
    const Sprite* sprite() {
        if (_sprites.size() == 0) return 0x0;
        if (_sprites.size() <= spriteIndex || spriteIndex < 0) {
            std::cout << "Sprite index is out of bounds.";
            return 0x0;
        }
        return _sprites[spriteIndex];
    }

    /**
     * @brief Executed everytime it cans.
     * @param deltaTime Time it took for the graphics to render the frame.
     */
    virtual void update(double deltaTime);
    
    /**
     * @brief On Scene Start.
     */
    virtual void start() {}
    
    /**
     * @brief Sets the collider for the next frame.
     */
    void setCollider(ColType col) {
        _collider = col;
        // PhysicsManager::... -> informChange(this, col);
    }
    
    /**
     * @brief Changes in shared pointers will be made at the end when no one is accessing it for sure.
     */
    void _end();
    
    /**
     * @brief deprecated for the moment
     */
    void _update() {
    }
    
    
    /**
     * @brief The unique instance ID
     */
    int instanceID() {
        return _instanceID;
    }
    
protected:

    /**
     * @brief Next frame will render the specified sprite index
     */
    void setSpriteIndex(int index) {
        spriteIndex = index;
    }
    
    /**
     * @brief executed on scene change
     */
    virtual void onExitScene() {}
    
    /**
     * @brief Fired everytime it collides with a GameObject which has a ColType that is not NULL.
     */
    virtual void onCollide(GameObject*, ColType*, ColFrom) {}
    
    
};

#endif /* GameObject_hpp */
