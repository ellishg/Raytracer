//
//  RenderEngine.cpp
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/23/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//

#include "SDLClass.h"

SDLClass::SDLClass()    {
    
    SDLWindow = nullptr;

    SDLRenderer = nullptr;
    
    SDLScreen = nullptr;
    
    isRunning = true;
    
    WWidth = WWIDTH;
    
    WHeight = WHEIGHT;
}

bool SDLClass::initialize() {
    
    if(SDL_Init(SDL_INIT_VIDEO))   {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    
    if (SDL_CreateWindowAndRenderer(WWidth, WHeight, SDL_WINDOW_RESIZABLE, &SDLWindow, &SDLRenderer) < 0) {
        fprintf(stderr, "CreateWindowAndRenderer failed: %s\n", SDL_GetError());
        return false;
    }
    
    SDLScreen = SDL_CreateTexture(SDLRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WWidth, WHeight);
    
    if (SDLScreen == NULL) {
        fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

void SDLClass::draw(uint32_t * pixelBuffer)   {
    
    SDL_UpdateTexture(SDLScreen, NULL, /*pixels*/ pixelBuffer, WWidth * sizeof(Uint32));
    
    
    SDL_RenderClear(SDLRenderer);
    SDL_RenderCopy(SDLRenderer, SDLScreen, NULL, NULL);
    SDL_RenderPresent(SDLRenderer);
}

void SDLClass::event()   {
    
    while (SDL_PollEvent(&Event)) {
        switch (Event.type) {
            case SDL_QUIT:
                OnExit();
                break;
            case SDL_KEYDOWN:
                OnKeyDown(Event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}

void SDLClass::OnKeyDown(SDL_Keycode sym)  {
    switch (sym) {
        case SDLK_ESCAPE:
            OnExit();
            break;
        default:
            break;
    }
}

void SDLClass::cleanUp()    {
    
    SDL_DestroyWindow(SDLWindow);
    
    SDL_Quit();
}