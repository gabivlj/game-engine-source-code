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
#include "./WindowManager.hpp"
#include "Types/Sprite.hpp"
#include "Types/GameObject.hpp"
#include "Types/Utils.hpp"
#include "StateManager.hpp"
#include <map>
#include <string>
#include <stdio.h>


class GraphicsManager : public Singleton<GraphicsManager> {
private:
    GraphicsManager() {
        
    }
    // TODO: Change int to SDL_Texture.
    std::map<const Sprite*, SDL_Texture*> textures;
    void render(GameObject* gameObject) {
        // Get the rect of the gameObject
        const SDL_Rect* endRect = ConversionSDL::pdtsdlrect(&gameObject->transform.position, &gameObject->transform.dimension);
        WindowManager::getInstance()->Render(textures.at(gameObject->sprite()), endRect);
    }
    
    SDL_Surface* loadSurface(std::string source) {
        //The final optimized image
        SDL_Surface* optimizedSurface = NULL;
        
        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(source.c_str());
        if (loadedSurface == NULL) {
            printf( "Unable to load image %s! SDL_image Error: %s\n", source.c_str(), IMG_GetError() );
        } else {
            //Convert surface to screen format
            optimizedSurface = SDL_ConvertSurface(loadedSurface, WindowManager::getInstance()->Surface()->format, 0);
            if (optimizedSurface == NULL) {
                printf( "Unable to optimize image %s! SDL Error: %s\n", source.c_str(), SDL_GetError() );
            }
            SDL_FreeSurface( loadedSurface );
        }
        
        return optimizedSurface;
    }
    
    bool update(GameObject** gameObjects, int length) {
        for (int i = 0; i < length; ++i) {
            GameObject* gameObject = gameObjects[i];
            render(gameObject);
        }
        return true;
    }
    
    bool end() {
        return true;
    }

public:
    bool start() {
        WindowManager::getInstance()->Initialize(1000, 1000);
        return true;
    }
    
    /**
     * @param source string of the path
     * @param dimensions dimensions of the sprite
     * @param position position of the sprite (0,0)?
     * @returns Sprite reference to add to your gameObject.
     */
    const Sprite* loadSprite(std::string source, dimensions dimensions, transform position) {
        const Sprite* sprite = new Sprite(source);
        SDL_Surface* surface = loadSurface(source);
        SDL_Texture* texture = WindowManager::getInstance()->CreateTexture(surface, ConversionSDL::pdtsdlrect(&position.position, &dimensions));
        textures.insert(std::pair<const Sprite*, SDL_Texture*> (sprite, texture));
        return sprite;
    }
        
};
#endif /* GraphicsManager_hpp */
