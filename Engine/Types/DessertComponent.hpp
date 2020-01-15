//
//  DessertComponent.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 15/01/2020.
//  Copyright © 2020 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef DessertComponent_hpp
#define DessertComponent_hpp

#include <stdio.h>
#include "../Singleton.hpp"

class StateManager;

class DessertComponent : Singleton<DessertComponent> {
public:
  
protected:
    friend StateManager;
    virtual void update() {}
    virtual void start() {}
private:
    friend StateManager;
};

#endif /* DessertComponent_hpp */
