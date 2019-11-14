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
#include <SDL.h>
#include <SDL_image.h>

#endif
#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif
#include "./Singleton.hpp"
#include "./WindowManager.hpp"
#include "Types/Sprite.hpp"
#include "Types/GameObject.hpp"
#include "Types/Utils.hpp"
#include "StateManager.hpp"
#include "CameraManager.hpp"
#include <map>
#include <string>
#include <stdio.h>


class GraphicsManager : public Singleton<GraphicsManager> {
private:
    
    
    friend StateManager;
    
    std::map<const Sprite*, SDL_Texture*> textures;
    std::map<const Sprite*, SDL_Rect*> positions;
    
    void render(GameObject* gameObject) {
        // Get the rect of the gameObject
        SDL_Rect* endRect = ConversionSDL::pdtsdlrect(&gameObject->form.position, &gameObject->form.dimension);
        CameraManager* camera = CameraManager::getInstance();
        WindowManager* W = WindowManager::getInstance();
        endRect->x = endRect->x - camera->position.x;
        endRect->y = endRect->x - camera->position.y;
        endRect->w = endRect->w;
        endRect->h = endRect->h;
        SDL_RenderSetLogicalSize(W->Renderer(), camera->size.width, camera->size.height);
        // Get the SDL_Texture and SDL_Rect where we have stored the sprite and pass it to the render texture method. We
        // also pass the endRect which is where we want it rendered (the position of the gameObject).
        WindowManager::getInstance()->renderTexture(textures.at(gameObject->sprite()), endRect, positions.at(gameObject->sprite()));
    }
    
    /**
     * @param source Where to get the surface image
     * @description Gets a surface from the specified source. (For texture rendering)
     */
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
    
    bool update(std::vector<GameObject*>* gameObjects, int length) {
        WindowManager::getInstance()->clearWindow();
        for (int i = 0; i < length; ++i) {
            GameObject* gameObject = (*gameObjects)[i];
            render(gameObject);
        }
        CameraManager* camera = CameraManager::getInstance();
        SDL_Rect topLeftViewport = *ConversionSDL::pdtsdlrect(&camera->viewportPosition, &camera->viewportDimensions);
        SDL_RenderSetViewport(WindowManager::getInstance()->Renderer(), &topLeftViewport);
        WindowManager::getInstance()->updateWindow();
        return true;
    }
    
    bool end() {
        
        return true;
    }
    
    bool start() {
       return true;
    }
       

public:
   
    GraphicsManager() {
        textures = std::map<const Sprite*, SDL_Texture*>();
        positions = std::map<const Sprite*, SDL_Rect*>();
        WindowManager::getInstance()->initialize(1000, 1000);
    }
    
    /**
     * @param source string of the path
     * @param dimensions dimensions of the sprite
     * @param position position of the sprite (0,0)?
     * @returns Sprite reference to add to your gameObject.
     * @description Loads a sprite. 1. Loads a surface. 2. Loads the texture from the surface and the SDL_Rect (the texture dimensions). 3. Adds it to the map of the textures and SDL_rects for rendering.
     */
    const Sprite* loadSprite(std::string source, dimensions dimensions, vec2 position) {
        const Sprite* sprite = new Sprite(source);
        SDL_Surface* surface = loadSurface(source);
        dimensions.width = surface->w;
        dimensions.height = surface->h;
        SDL_Rect* rect = ConversionSDL::pdtsdlrect(&position, &dimensions);
        SDL_Texture* texture = WindowManager::getInstance()->createTexture(surface, rect);
        positions.insert(std::pair<const Sprite*, SDL_Rect*> (sprite, rect));
        textures.insert(std::pair<const Sprite*, SDL_Texture*> (sprite, texture));
        return sprite;
    }
        
};
#endif /* GraphicsManager_hpp */
