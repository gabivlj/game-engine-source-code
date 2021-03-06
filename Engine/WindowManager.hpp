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
#include <SDL_image.h>
#endif
#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif


class WindowManager : public Singleton<WindowManager> {
    bool initialized = false;
public:
    friend class Singleton<WindowManager>;
   
    int SCREEN_H = 1000;
    int SCREEN_W = 1000;
    
    /**
     * @param SCREEN_HEIGHT The screen height
     * @param SCREEN_WIDTH The screen width
     * @brief Initializes the window.
    */
    void initialize (int SCREEN_HEIGHT, int SCREEN_WIDTH) {
        if (initialized) return;
        initialized = true;
        SCREEN_W = SCREEN_WIDTH;
        SCREEN_H = SCREEN_HEIGHT;
        int flag = 0;
        int flagRenderer = SDL_RENDERER_SOFTWARE;
#ifdef _WIN32
        flag = SDL_WINDOW_OPENGL;
        flagRenderer = SDL_RENDERER_SOFTWARE;
#else
        flag = 0;
#endif
        w = SDL_CreateWindow("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flag);
        
        r = SDL_CreateRenderer(w, -1, flagRenderer);
        s = SDL_GetWindowSurface(w);

        if (s == NULL) {
            printf("Unable Surface: %s", SDL_GetError());
        }
        
        if (r == NULL) {
            printf("Unable to load renderer! SDL_image Error: %s\n", SDL_GetError());
        }
        SDL_RenderSetLogicalSize(r, SCREEN_WIDTH, SCREEN_HEIGHT);
        
    }
    
    const SDL_Surface* Surface() {
        return s;
    }
    
    const SDL_Window* Window() {
        return w;
    }
    
    SDL_Renderer* Renderer() {
        return r;
    }
    
    SDL_Texture* createTexture(SDL_Surface* surface, const SDL_Rect* rect) {
        if (!r) {
            printf("\nRenderer not initalized\n");
        }
        SDL_Texture* t = SDL_CreateTextureFromSurface(r, surface);
        SDL_RenderCopy(r, t, rect, rect);
        
        return t;
    }
    
    /**
     * @brief Don't use this. We already use RenderTexture()
     * @deprecated
     */
    void Render(SDL_Texture* t, const SDL_Rect* rect) {
        SDL_Point p;
        SDL_Rect reeect;
        reeect = { rect->x, rect->y, rect->w, rect->h };
        p.x = rect->x + rect->w / 2;
        p.y = rect->y + rect->h / 2;
        double flip = 0;
        SDL_RenderCopyEx(r, t, rect, &reeect, flip, &p, SDL_FLIP_NONE);
    }
    
    void updateWindow() {
        SDL_RenderPresent(r);
    }

    /**
     * @deprecated
     * @see GraphicsManager::renderLine()
     */
    void drawLines(const SDL_Point* points, int len) {
        SDL_RenderDrawLines(r, points, len);
    }
    
    void renderSquare(const SDL_Rect* rect) {
        SDL_SetRenderDrawColor(r, 100, 100, 100, 1);
        SDL_RenderDrawRect(r, rect);
        SDL_FRect rectF = {static_cast<float>(rect->x), static_cast<float>(rect->y), static_cast<float>(rect->w), static_cast<float>(rect->h)};
        SDL_RenderFillRectF(r, &rectF);
    }
    
    /**
     * @param t Texture to render
     * @param rect Where to render
     * @param image_rect Where is the original texture stored
     * @brief Copies a texture from image_rect and renders it on rect
     */
    void renderTexture(SDL_Texture* t, const SDL_Rect* rect, const SDL_Rect* image_rect) {
         SDL_RenderCopy(r, t, image_rect, rect);
    }
    
    /**
     * @brief Clears the window
     */
    void clearWindow() {
        SDL_SetRenderDrawColor(r, 1, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(r);
    }
    
    void FillSurface(Uint8 r, Uint8 g, Uint8 b) {
        SDL_FillRect(s, NULL, SDL_MapRGB(s->format, r, g, b));
        updateWindow();
    }
    
    /**
     * @brief Destroys the window.
     */
    void destroy() {
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
