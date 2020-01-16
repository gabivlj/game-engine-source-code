//
//  Sound.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 15/01/2020.
//  Copyright © 2020 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Sound_hpp
#define Sound_hpp

#include <stdio.h>
#include <string>
#ifdef _WIN32
#include "SDL_mixer"
#endif
#if __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#endif


#define DESSERT_SOUND_EFFECT 1
#define DESSERT_MUSIC        2

typedef u_int8_t track_type;

class SoundManager;

class Sound {
public:
    const char* path;
    track_type type;
    
    Sound(const char* p, track_type t) {
        path = p;
        type = t;
    }
    
    ~Sound() {
        if (SDL_sound_effect) Mix_FreeChunk(SDL_sound_effect);
        if (SDL_music) Mix_FreeMusic(SDL_music);
    }
    
private:
    bool playing = false;
    friend SoundManager;
    Mix_Music* SDL_music;
    Mix_Chunk* SDL_sound_effect;
};

#endif /* Sound_hpp */
