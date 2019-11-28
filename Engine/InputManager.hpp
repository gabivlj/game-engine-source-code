//
//  InputManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 13/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#define UP 0b00010000
#define LEFT 0b00100000
#define RIGHT 0b01000000
#define DOWN 0b10000000

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

typedef u_int8_t key;

class StateManager;

class InputManager : public Singleton<InputManager> {
    
    friend StateManager;
    u_int8_t inputs = 0;

    void changeKeyDown(SDL_Event& e) {
       switch(e.key.keysym.sym){
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
           default:
               break;
       }
    }
    
    void changeKeyUp(SDL_Event& e) {
        switch(e.key.keysym.sym){
            case SDLK_LEFT:
                inputs = KEY_UP(inputs, LEFT);
                break;
            case SDLK_RIGHT:
                inputs = KEY_UP(inputs, RIGHT);
                break;
            case SDLK_UP:
                inputs = KEY_UP(inputs, UP);
                printf("%d", inputs);
                break;
            case SDLK_DOWN:
                inputs = KEY_UP(inputs, DOWN);
                break;
            default:
                break;
        }
    }

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
    
    bool getInput(key k) {
        return (inputs & k) == k;
    }
    
};

#endif /* InputManager_hpp */
