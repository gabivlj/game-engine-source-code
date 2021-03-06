//
//  Singleton.hpp
//  Engine19
//
//  Created by Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla on 03/10/2019.
//  Copyright © 2019 Created by Gabriel Villalonga Simón, Daniel Gracia Machado and Jorge Solano Pinilla. All rights reserved.
//

#ifndef Singleton_hpp
#define Singleton_hpp

#include <stdio.h>

template <class A>
class Singleton {
private:
    static A* instance;
    friend A;
public:
    inline static A* createInstance() {
        if (instance == NULL)
            instance = new A();
        return instance;
    }
    inline static A* getInstance() {
        if (instance == NULL) {
            instance = new A();
        }
        return instance;
    }

    
    
};

template<class A>
A *Singleton<A>::instance = NULL;



#endif /* Singleton_hpp */
