//
//  SDLClass.h
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/23/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __NewRaytracer__SDLClass__
#define __NewRaytracer__SDLClass__

#include "SDL2/SDL.h"

#include "Definitions.h"

class SDLClass {
    
    SDL_Window * SDLWindow;
    
    SDL_Renderer * SDLRenderer;
    
    uint32_t WWidth, WHeight;
    
    SDL_Texture * SDLScreen;
    
    SDL_Event Event;
    
public:
    
    bool isRunning;
    
    SDLClass();
    
    bool initialize();
    
    void draw(uint32_t * pixelBuffer);
    
    void event();
    
    void OnKeyDown(SDL_Keycode sym);
    
    void cleanUp();
    
    void OnExit() {isRunning = false;}
};

#endif /* defined(__NewRaytracer__SDLClass__) */
