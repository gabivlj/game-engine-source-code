//
//  GraphicsManager.hpp
//  Engine19
//
//  Created by Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 17/10/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
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
#include <queue>
#include <string>
#include <stdio.h>

class GameObjectHelper;

class GraphicsException : public std::exception {
    
public:
    GraphicsException(std::string what) {
        w = what;
    }
private:
    std::string w;
    virtual const char* what() const throw() {
        return std::string("Exception on GraphicsManager: " + w).c_str();
    }
};


class GraphicsManager : public Singleton<GraphicsManager> {
private:
    
    bool SAVE = false;
    
    friend StateManager;
    friend GameObjectHelper;
    friend void nonGraphicsRelatedUpdate();
    friend bool waitUntilUpdateFinishes();
    
    typedef struct {
        SDL_Point p1;
        SDL_Point p2;
    } SDL_Line;

    
    std::map<const Sprite*, SDL_Texture*> textures;
    std::map<const Sprite*, SDL_Rect*> positions;
    
    /**
     * @discussion I really don't know how (and I don't have time as well) to sync this method call to the GraphicsManager render. If you have any idea feel free to add the code lol. - Gabi.
     */
    void renderLine(line l) {
        
    }
    
    /**
     * @discussion Basically this method renders a GameObject (If it detects that it doesn't have a sprite tries to render a square)
     */
    void render(GameObject* gameObject) {
        // Get the rect of the gameObject
        SDL_Rect* endRect = ConversionSDL::tosdlrect(&gameObject->form.position, &gameObject->form.dimension);
        // Declarations
        CameraManager* camera = CameraManager::getInstance();
        WindowManager* W = WindowManager::getInstance();
        // Modify rect of the sprite depending on camera position.
        endRect->x = endRect->x - camera->position.x;
        endRect->y = endRect->y - camera->position.y;
        // Set logical size of the camera.
        SDL_RenderSetLogicalSize(W->Renderer(), camera->size.width, camera->size.height);
        // Get the SDL_Texture and SDL_Rect where we have stored the sprite and pass it to the render texture method. We
        // also pass the endRect which is where we want it rendered (the position of the gameObject).
        if (!gameObject->sprite()) {
            W->renderSquare(endRect);
            return;
        }
        const Sprite* spr = gameObject->sprite();
        SDL_Texture* texture = textures[spr];
        W->renderTexture(texture, endRect, positions[spr]);
    }
    
    /**
     * @param source Where to get the surface image
     * @discussion Gets a surface from the specified source. (For texture rendering)
     */
    SDL_Surface* loadSurface(std::string source) {
        //The final optimized image
        SDL_Surface* optimizedSurface = NULL;
        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(source.c_str());
        if (loadedSurface == NULL) {
            printf( "Unable to load image %s! SDL_image Error: %s\n", source.c_str(), IMG_GetError() );
            throw new GraphicsException("Unable to open the image, either the path doesn't exist or it is not a supported format.");
        } else {
            //Convert surface to screen format
            optimizedSurface = SDL_ConvertSurface(loadedSurface, WindowManager::getInstance()->Surface()->format, 0);
            
            if (optimizedSurface == NULL) {
                printf("Unable to optimize image %s! SDL Error: %s\n", source.c_str(), SDL_GetError());
                throw new GraphicsException("Unable to optimize the image! SDL_Error above.");
            }
            SDL_FreeSurface( loadedSurface );
        }
        
        return optimizedSurface;
    }
    
    /**
     * @discussion Updates the graphics manager.
     * @param gameObjects The gameObjects reference to the original source to render. Take into mind that in development of the engine we shouldn't access this gameObject vector while accessing it on the front-end because race conditions.
     */
    bool update(std::vector<GameObject*>* gameObjects, int length) {
        WindowManager::getInstance()->clearWindow();
        SAVE = false;
        for (int i = 0; i < length; ++i) {
            GameObject* gameObject = (*gameObjects)[i];
            gameObject->_endedFrame = false;
            render(gameObject);
        }
    
        // Render.
        CameraManager* camera = CameraManager::getInstance();
        SDL_Rect topLeftViewport = *ConversionSDL::tosdlrect(&camera->viewportPosition, &camera->viewportDimensions);
        SDL_RenderSetViewport(WindowManager::getInstance()->Renderer(), &topLeftViewport);
        WindowManager::getInstance()->updateWindow();
        SAVE = true;
        return true;
    }
    
    bool end() {
        WindowManager::getInstance()->destroy();
        delete this;
        return true;
    }
    
    bool start() {
       return true;
    }
       

public:
    
    ~GraphicsManager() {
        textures.clear();
        positions.clear();
    }
   
    GraphicsManager() {
        textures = std::map<const Sprite*, SDL_Texture*>();
        positions = std::map<const Sprite*, SDL_Rect*>();
        WindowManager::getInstance()->initialize(1000, 1000);
        SAVE = true;
    }
    
    /**
     * @param source string of the path
     * @param dimensions dimensions of the sprite
     * @param position position of the sprite (0,0)?
     * @throws GraphicsException if: the source does not exist, or the image format is not supported. You can catch it if you want so your game doesn't give a single sh*t about sprites.
     * @returns Sprite reference to add to your gameObject.
     * @description Loads a sprite. 1. Loads a surface. 2. Loads the texture from the surface and the SDL_Rect (the texture dimensions). 3. Adds it to the map of the textures and SDL_rects for rendering.
     */
    const Sprite* loadSprite(std::string source, dimensions dimensions, vec2 position) {
        if (!SAVE) return NULL;
        const Sprite* sprite = new Sprite(source);
        SDL_Surface* surface = loadSurface(source);
        if (!surface) {
            return NULL;
        }
        dimensions.width = surface->w;
        dimensions.height = surface->h;
        SDL_Rect* rect = ConversionSDL::tosdlrect(&position, &dimensions);
        SDL_Texture* texture = WindowManager::getInstance()->createTexture(surface, rect);
        positions.insert(std::pair<const Sprite*, SDL_Rect*> (sprite, rect));
        textures.insert(std::pair<const Sprite*, SDL_Texture*> (sprite, texture));
        return sprite;
    }
        


};

#endif /* GraphicsManager_hpp */
