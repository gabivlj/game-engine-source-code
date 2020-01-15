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
#include <vector>

#include "./Types/Sound.hpp"
#include "../Engine/Types/DessertComponent.hpp"

class SoundManager : DessertComponent {
public:
    void addSound() {}
private:
    std::vector<Sound*> sounds;
    void update() override {
        
    }
};

#endif /* SoundManager_hpp */
