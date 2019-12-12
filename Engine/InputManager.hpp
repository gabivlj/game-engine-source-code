//
//  InputManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 13/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp

/**
 * @abstract Key declarations
 */
#define UP    0b000100000
#define LEFT  0b001000000
#define RIGHT 0b010000000
#define DOWN  0b100000000
#define W_K   0b000010000
#define S_K   0b000001000
#define A_K   0b000000100
#define D_K   0b000000010
#define ESC_K 0b000000001

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#endif
#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

#include <stdio.h>
#include "./Singleton.hpp"

// Press operation
#define PRESS(a, b) ((a ^ b) & b) == b ? a ^ b : a
// Key Up Method definition
#define KEY_UP(a, b) ((a ^ b) & b) == b ? a : a ^ b

typedef uint16_t key;

class StateManager;


/**
 * @description Static class that should only be used to gathering inputs.
 */
class InputManager : public Singleton<InputManager> {
    
    friend StateManager;
    /**
     * @discussion Basically this stores all of the inputs of the engine in a 8 bit variable.
     */
    uint16_t inputs = 0;

    /**
     * @abstract On key down this should be fired.
     * @param e SDL_Event
     */
    void changeKeyDown(SDL_Event& e) {
       switch(e.key.keysym.sym){
           case SDLK_ESCAPE:
               inputs = PRESS(inputs, ESC_K);
           case SDLK_LEFT:
               inputs = PRESS(inputs, LEFT);
               break;
           case SDLK_RIGHT:
               inputs = PRESS(inputs, RIGHT);
               break;
           case SDLK_UP:
               inputs = PRESS(inputs, UP);
               break;
           case SDLK_DOWN:
               inputs = PRESS(inputs, DOWN);
               break;
           case SDLK_w:
               inputs = PRESS(inputs, W_K);
               break;
           case SDLK_s:
               inputs = PRESS(inputs, S_K);
               break;
           case SDLK_a:
               inputs = PRESS(inputs, A_K);
               break;
           case SDLK_d:
               inputs = PRESS(inputs, D_K);
               break;
           default:
               break;
       }
    }
    
    /**
     * @abstract On key up this should be fired.
     * @param e SDL_Event
     */
    void changeKeyUp(SDL_Event& e) {
        switch(e.key.keysym.sym){
            case SDLK_ESCAPE:
                inputs = KEY_UP(inputs, ESC_K);
            case SDLK_LEFT:
                inputs = KEY_UP(inputs, LEFT);
                break;
            case SDLK_RIGHT:
                inputs = KEY_UP(inputs, RIGHT);
                break;
            case SDLK_UP:
                inputs = KEY_UP(inputs, UP);
                break;
            case SDLK_DOWN:
                inputs = KEY_UP(inputs, DOWN);
                break;
            case SDLK_w:
                inputs = KEY_UP(inputs, W_K);
                break;
            case SDLK_s:
                inputs = KEY_UP(inputs, S_K);
                break;
            case SDLK_a:
                inputs = KEY_UP(inputs, A_K);
                break;
            case SDLK_d:
                inputs = KEY_UP(inputs, D_K);
                break;
            default:
                break;
        }
    }

    /**
     * @param e SDL_Event
     */
    void processEvent(SDL_Event& e) {
       switch(e.type) {
           case SDL_KEYUP:
               changeKeyUp(e);
               break;
           case SDL_KEYDOWN:
               changeKeyDown(e);
               break;
           default:
               break;
       }
    }

    void update(SDL_Event& e) {
       processEvent(e);
    }
    
public:
    
    InputManager() {}
    
    /**
     * @param k the key that you want
     * @description Returns if the passed key is being pressed.
     */
    bool getInput(key k) {
        return (inputs & k) == k;
    }
    
};


#endif /* InputManager_hpp */
