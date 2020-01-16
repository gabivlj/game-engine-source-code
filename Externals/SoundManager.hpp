//
//  SoundManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 15/01/2020.
//  Copyright © 2020 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef SoundManager_hpp
#define SoundManager_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include "./Types/Sound.hpp"
#include "../Engine/Types/DessertComponent.hpp"

class SoundManager : public DessertComponent {
public:
    
    Sound* loadSound(const char* path) {
        Sound* sound = new Sound(path, DESSERT_SOUND_EFFECT);
        sound->SDL_sound_effect = Mix_LoadWAV(path);
        if (!sound->SDL_sound_effect) {
            std::cout << "Sound not loaded... " << std::endl << Mix_GetError() << std::endl;
        }
        sounds.push_back(sound);
        return sound;
    }
    
    Sound* loadMusic(const char* path) {
        Sound* sound = new Sound(path, DESSERT_MUSIC);
        sound->SDL_music = Mix_LoadMUS(path);
        sounds.push_back(sound);
        return sound;
    }
    
    void reset() {
        Mix_HaltMusic();
    }
    
    void play(Sound* sound) {
        sound->playing = true;
    }
    
    void stop(Sound* sound) {
        sound->playing = false;
    }
    
    SoundManager() : DessertComponent() {
        if (initialized) return;
        initialized = true;
        if (!SDL_Init(SDL_INIT_AUDIO)) {
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;                
            }
            return;
        }
        std::cout
            << "Error initializing the Sound component. SDL_ERROR:\n"
            << SDL_GetError()
            << std::endl;
    }
    
    
    
private:
    bool initialized = false;
    std::vector<Sound*> sounds;
    
    void onSceneChange() override {
        
    }
    
    void start() override {
        for (const auto& sound : sounds) {
            sound->playing = false;
            if (Mix_PlayingMusic()) {
                Mix_HaltMusic();
            }
        }
    }
    
    void end() override {
        for (const auto& sound : sounds) {
            delete sound;
        }
        
        sounds.clear();
    }
    
    void update() override {
        for (auto& sound : sounds) {
            // LOTS of cache misses with this, but I ain't got time for optimizing lol. The cool solution would be having a vector of only the sounds that we are gonna play so there isn't cache misses
            // But this engine isn't a data oriented engine so idc ¯\_(ツ)_/¯
            if (!sound->playing) {
                if (sound->type == DESSERT_MUSIC && Mix_PlayingMusic()) {
                    Mix_PauseMusic();
                }
                continue;
            }
            if (sound->type == DESSERT_SOUND_EFFECT) Mix_PlayChannel(-1, sound->SDL_sound_effect, 0);
            else {
                if (!Mix_PlayingMusic()) {
                    Mix_PlayMusic(sound->SDL_music, -1);
                }
                if (Mix_PausedMusic()) {
                    Mix_ResumeMusic();
                }
            }
        }
    }
};

static SoundManager soundManager;

#endif /* SoundManager_hpp */
