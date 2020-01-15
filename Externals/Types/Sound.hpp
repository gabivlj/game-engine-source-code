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

#include <SDL2_mixer/SDL_mixer.h>

#define DESSERT_SOUND_EFFECT 1
#define DESSERT_MUSIC        2


class SoundManager;

typedef struct {
    std::string path;
private:
    friend SoundManager;
    Mix_Music* SDL_music;
    Mix_Chunk* SDL_sound_effect;
} Sound;

#endif /* Sound_hpp */
