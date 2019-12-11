//
//  StateManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 11/11/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
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
    bool finishedLoop = false;
    bool ended = true;
    
    StateManager() {}
    
    /**
     * @brief End the app.
     */
    void exit() {
        end();
    }

    
    
private:
    
    friend void exit();
    friend bool waitUntilUpdateFinishes();
    friend void nonGraphicsRelatedUpdate();
    friend SceneManager;
    void start(Scene*);
    void update();
    void end();
    Scene* nextScene;
    
protected:
    
};




#endif /* StateManager_hpp */
