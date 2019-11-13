//
//  WindowManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 07/10/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef WindowManager_hpp
#define WindowManager_hpp

#include <stdio.h>
#include "./Singleton.hpp"

#ifdef _WIN32
#include <SDL.h>
#endif
#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif


class WindowManager : public Singleton<WindowManager> {
    bool initialized = false;
public:
    friend class Singleton<WindowManager>;
    void Initialize (int SCREEN_HEIGHT, int SCREEN_WIDTH) {
        if (initialized) return;
        initialized = true;
        w = SDL_CreateWindow("My game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        s = SDL_GetWindowSurface(w);
        r = SDL_GetRenderer(w);
        SDL_RenderSetLogicalSize(r, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (r == NULL) {
            printf( "Unable to load renderer! SDL_image Error: %s\n", SDL_GetError());
        }
    }
    const SDL_Surface* Surface() {
        return s;
    }
    
    const SDL_Window* Window() {
        return w;
    }
    
    SDL_Texture* CreateTexture(SDL_Surface* surface, const SDL_Rect* rect) {
        if (!r) {
            printf("\nRenderer not initalized\n");
        }
        SDL_Texture* t = SDL_CreateTextureFromSurface(r, surface);
        SDL_RenderCopy(r, t, rect, rect);

        return t;
    }
    
    void Render(SDL_Texture* t, const SDL_Rect* rect) {
        SDL_Point p;
        SDL_Rect reeect;
        reeect = SDL_Rect { rect->x, rect->y, rect->w, rect->h};
        p.x = rect->w / 2;
        p.y = rect->h / 2;
        double flip = 0;
        SDL_RenderCopyEx(r, t, rect, &reeect, flip, &p, SDL_FLIP_NONE);
    }
    
    void UpdateWindow() {
        SDL_RenderPresent(r);
    }
    
    void RenderTexture(SDL_Texture* t, SDL_Rect* rect) {
         SDL_RenderCopy(r, t, NULL, NULL);
    }
    
    void clearWindow() {
        SDL_SetRenderDrawColor(r, 1, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(r);
    }
    
    void FillSurface(Uint8 r, Uint8 g, Uint8 b) {
        SDL_FillRect(s, NULL, SDL_MapRGB(s->format, r, g, b));
        UpdateWindow();
    }
    
    void Destroy() {
        SDL_DestroyWindow(w);
    }
    
private:
    SDL_Window* w;
    SDL_Surface* s;
    SDL_Renderer* r;
    int screenWidth;
    int screenHeight;
    WindowManager() {}
};

#endif /* WindowManager_hpp */
