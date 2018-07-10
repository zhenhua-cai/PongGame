//
//  pong.cpp
//  GameProject
//
//  Created by Zhenhua Cai on 7/9/18.
//  Copyright © 2018 Zhenhua Cai. All rights reserved.
//

#include "pong.hpp"
#include<SDL2/SDL.h>
#include<ctime>
#include<cstdlib>
Pong::Pong():isRunning(true),window(nullptr),renderer(nullptr),tickCount(0){
    srand(int(time(nullptr)));
    //ball position
    ballP={
        WIDTH/2,
        HEIGHT/2
    };
    //left paddle position
    paddlePL={
        THICKNESS/2,
        HEIGHT/2
    };
    //right paddle position
    paddlePR={
        WIDTH-THICKNESS/2,
        HEIGHT/2
    };
    //set the velocity of the ball
    velocity={
        double(WIDTH)/(rand()%3+5),
        double(HEIGHT)/(rand()%2+3)
    };
}
bool Pong::init(){
    //initialize game
    int result=SDL_Init(SDL_INIT_EVERYTHING);
    if(result!=0){
        SDL_Log("Fail to initialize the game %s",SDL_GetError());
        return false;
    }
    //create window
    window=SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if(nullptr==window){
        SDL_Log("Fail to create window %s",SDL_GetError());
        return false;
    }
    //create renderer
    renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(nullptr==renderer){
        SDL_Log("Fail to create renderer %s",SDL_GetError());
        return false;
    }
    return true;
}
void Pong::runLoop(){
    while(isRunning){
        processInput();
        updateData();
        generateOutput();
    }
}

void Pong::exit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void Pong::processInput(){
    SDL_Event event;
    //press X to exit the game
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                isRunning=false;
        }
    }
    //if press esc, then exit the game
    const Uint8 * state=SDL_GetKeyboardState(nullptr);
    if(state[SDL_SCANCODE_ESCAPE]){
        isRunning=false;
    }
}
void Pong::updateData(){
    //TODO: updateData method;
    float deltaTime=(SDL_GetTicks()-tickCount)/1000.0f;
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), tickCount+16));
    
    if(deltaTime>0.05f){
        deltaTime=0.05f;
    }
    //move the paddles
    const Uint8 * state=SDL_GetKeyboardState(nullptr);
    //left paddle
    if(state[SDL_SCANCODE_W]){
        paddlePL.y-=(PADDLESPEED)*deltaTime;
        if(paddlePL.y<THICKNESS+PADDLEW/2){
            paddlePL.y=THICKNESS+PADDLEW/2;
        }
    }
    else if(state[SDL_SCANCODE_S]){
        paddlePL.y+=(PADDLESPEED)*deltaTime;
        if(paddlePL.y>HEIGHT-THICKNESS-PADDLEW/2){
            paddlePL.y=HEIGHT-THICKNESS-PADDLEW/2;
        }
    }
    //right paddle
    if(state[SDL_SCANCODE_UP]){
        paddlePR.y-=(PADDLESPEED)*deltaTime;
        if(paddlePR.y<THICKNESS+PADDLEW/2){
            paddlePR.y=THICKNESS+PADDLEW/2;
        }
    }
    else if(state[SDL_SCANCODE_DOWN]){
        paddlePR.y+=(PADDLESPEED)*deltaTime;
        if(paddlePR.y>HEIGHT-THICKNESS-PADDLEW/2){
            paddlePR.y=HEIGHT-THICKNESS-PADDLEW/2;
        }
    }
    
    
    //ball movement
    // left right
    ballP.x+=velocity.x*deltaTime;
    if(ballP.x<=THICKNESS*1.5&&velocity.x<0
       &&(ballP.y>=paddlePL.y-PADDLEW/2)
       &&(ballP.y<=paddlePL.y+PADDLEW/2))
    {
        velocity.x*=-1;
        velocity.x++;
        velocity.y*=1.01;
    }
    else if(ballP.x>=WIDTH-THICKNESS*1.5&&velocity.x>0
            &&(ballP.y>=paddlePR.y-PADDLEW/2)
            &&(ballP.y<=paddlePR.y+PADDLEW/2)
        )
    {
        velocity.x*=-1;
        velocity.x--;
        velocity.y*=1.01;
    }
    else if(ballP.x<=THICKNESS/2||ballP.x>=WIDTH-THICKNESS/2){
        velocity.x=velocity.y=0;
    }
    
    
    //up down
    ballP.y+=velocity.y*deltaTime;
    if(ballP.y>=HEIGHT-THICKNESS*1.5&&velocity.y>0){
        velocity.y*=-1;
    }
    else if(ballP.y<=THICKNESS*1.5&&velocity.y<0){
        velocity.y*=-1;
    }
    
    tickCount=SDL_GetTicks();
}
void Pong::generateOutput(){
    //draw the background of game.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    //draw the boder
    SDL_SetRenderDrawColor(renderer, 133, 50, 2, 255);
    SDL_Rect wall{
        0,0,
        WIDTH,THICKNESS
    };
    SDL_RenderFillRect(renderer, &wall);
    wall.y=HEIGHT-THICKNESS;
    SDL_RenderFillRect(renderer, &wall);
    
    //draw the ball
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    SDL_Rect ball{
        ballP.x-THICKNESS/2,
        ballP.y-THICKNESS/2,
        THICKNESS,
        THICKNESS
    };
    SDL_RenderFillRect(renderer, &ball);
    
    //draw the left paddle
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect paddleL{
        paddlePL.x-THICKNESS/2,
        paddlePL.y-PADDLEW/2,
        THICKNESS,
        PADDLEW
    };
    SDL_RenderFillRect(renderer, &paddleL);
    
    //draw the right paddle
    SDL_Rect paddleR{
        paddlePR.x-THICKNESS/2,
        paddlePR.y-PADDLEW/2,
        THICKNESS,
        PADDLEW
    };
    SDL_RenderFillRect(renderer, &paddleR);
    
    SDL_RenderPresent(renderer);
}
