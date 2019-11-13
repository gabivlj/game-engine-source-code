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
#include "./Singleton.hpp"
#include "./Types/Scene.hpp"


class SceneManager : public Singleton<SceneManager> {
private:
    std::vector<Scene*> scenes;
public:
    SceneManager() {
        scenes = std::vector<Scene*>();
    }
    bool addScene(Scene* sceneToAdd);
    
    bool changeToScene(Scene* sceneToChangeTo);
    
    bool changeToScene(int index);
};

#endif /* SceneManager_hpp */
