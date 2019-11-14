//
//  StateManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 11/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef StateManager_hpp
#define StateManager_hpp

#include <stdio.h>
#include "Singleton.hpp"
#include "GameObjectManager.hpp"


// Predeclaration for the scene.
class Scene;
class SceneManager;

class StateManager : public Singleton<StateManager> {
public:
    bool playing = false;
    StateManager() {}
private:
    
    friend void graphicsThreadUpdate();
    friend SceneManager;
    void start(Scene*);
    void update();
    void end();
    
protected:
    
};

#endif /* StateManager_hpp */
