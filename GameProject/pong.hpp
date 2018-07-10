//
//  pong.hpp
//  GameProject
//
//  Created by Zhenhua Cai on 7/9/18.
//  Copyright © 2018 Zhenhua Cai. All rights reserved.
//

#ifndef pong_hpp
#define pong_hpp

#include <stdio.h>
#include<SDL2/SDL.h>

class Pong{
    
private:
    enum{WIDTH=1024,HEIGHT=768,PADDLEW=100,THICKNESS=20,PADDLESPEED=350};
    struct Position{
        double x;
        double y;
    };
    struct Velocity{
        double x;
        double y;
    };
    SDL_Rect ballP;
    Velocity velocity;
    SDL_Rect paddlePL;
    SDL_Rect paddlePR;
    
    bool isRunning;
    Uint32 tickCount;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    void processInput();
    void updateData();
    void generateOutput();
public:
    Pong();
    bool init();
    void runLoop();
    void exit();
};

#endif /* pong_hpp */
