//
//  GraphicsManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 17/10/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef GraphicsManager_hpp
#define GraphicsManager_hpp

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#if __APPLE__
#include <SDL2/SDL.h>
#endif
#include "./Singleton.hpp"
#include "Types/Sprite.hpp"
#include "Types/GameObject.hpp"
#include <map>
#include <string>




#include <stdio.h>
class GraphicsManager : public Singleton<GraphicsManager> {
private:
    GraphicsManager() {}
    // TODO: Change int to SDL_Texture.
    std::map<const Sprite*, int> textures;
    void Render(GameObject* gameObject) {}

public:
    
    const Sprite* LoadSprite(std::string source) {
        const Sprite* sprite = new Sprite(source);
        textures.insert(std::pair<const Sprite*, int> (sprite, 0));
        return sprite;
    }
    
    bool Update(GameObject** gameObjects, int length) {
        for (int i = 0; i < length; ++i) {
//            gameObjects[i]->
        }
        return true;
    }
    
};
#endif /* GraphicsManager_hpp */
