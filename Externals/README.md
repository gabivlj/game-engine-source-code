## Externals Folder
### This folder serves the purpose of saving  the optional parts of the Engine

## How do I use the Dessert component system?

``` C++

#include "../Engine/Types/DessertComponent.hpp"

class YourOwnManager : public DessertComponent {
public:
    // snip of code
private:

    void update() override {
        // What do you want to happen meanwhile the game is executing?
    }
    
    void start() override {
        // Everytime a scene is started
    }
    
    void onSceneChange() override {
        // When a scene is changed
    }
    
    void end() override {
        // When the game is finished...
    }
    
};
    
    static YourOwnManager yourOwnManager;

```

### Then, inside the game init.

``` C++
#include "../Engine/Engine.hpp"

int main() {
// ......
    Dessert::LoadComponent(&yourOwnManager);
// ....
}
```

See more examples on how to use the engine in SpaceInvaders folder!
