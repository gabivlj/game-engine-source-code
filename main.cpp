////  PROJECT WITH SDL IN MAC/WINDOWS
////  Created by Gabriel Villalonga Simón and Daniel Gracia on 15/09/2019.
////  Copyright © 2019 Gabriel Villalonga Simón and Daniel Gracia. All rights reserved.
////
////  @@@@@@ This main is a test target for checking that all the libraries of this project work properly! @@@@@@
////      If Engine19 main.cpp is able to create the target, all is going right in your project configuration.
////  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <iostream>
#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#if __APPLE__
#include <SDL2/SDL.h>
#endif


int Test();

int main(int arg, char* args[]) {
    Test();
}


int Test() {
    
    
//    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//        std::cout << "Error with SDL init! SDL ERROR: " << SDL_GetError() << std::endl;
//    }
//    WindowManager* w = WindowManager::createInstance();
//    w->Initialize(1920, 1080);
////    w->FillSurface(255, 0, 0);
//    GameObject* gm = new GameObject();
//    gm->x = 20;
//    gm->y = 20;
//    GameObject* gm2 = new GameObject();
//    gm2->x = 10;
//    gm2->y = 10;
//    gm->SetSprite("/src/loaded.png", 1000, 1000, 100, 100);
//    gm2->SetSprite("/src/loaded.png", 1000, 1000, 100, 100);
//    SDL_Event e;
//    bool quit = false;
//    while (!quit){
//        while (SDL_PollEvent(&e)) {
//            InputManager* input = InputManager::createInstance();
//            bool up = input->GetAxis(ARROW_UP);
//            bool down = input->GetAxis(ARROW_DOWN);
//            if (e.type == SDL_QUIT){
//                quit = true;
//            }
//            w->clearWindow();
//            gm->y += (int)up * 10;
//            gm->y += (int)down * -10;
//
//            gm2->y += (int)up * 10;
//            gm2->y += (int)down * -10;
//            gm->update();
//            gm2->update();
//            w->UpdateWindow();
//        }
//    }
//    w->Destroy();
//    SDL_Quit();
//    return 0;

}
