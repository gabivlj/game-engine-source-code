//
//  SceneManager.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 13/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include <vector>
#include "./Types/Scene.hpp"
#include "./Singleton.hpp"

class SceneManager : public Singleton<SceneManager> {
private:
    std::vector<Scene*> scenes;
    
public:
    bool addScene(Scene* sceneToAdd) {
        scenes.push_back(sceneToAdd);
        return true;
    }
    
    bool changeToScene(Scene* sceneToChangeTo) {
        for (int i = 0; i < scenes.size(); ++i) {
            if (scenes[i] == sceneToChangeTo) {
                return true;
            }
        }
        return false;
    }
    
    bool changeToScene(int index) {
        if (index < scenes.size()) {
            return true;
        }
        return false;
    }
    
};

#endif /* SceneManager_hpp */
