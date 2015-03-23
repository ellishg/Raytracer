//
//  main.cpp
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/23/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//

#include "SDLClass.h"
#include "Raytracer.h"

#include <time.h>

int main(int argc, const char * argv[]) {
    
    clock_t t = clock();
    
    SDLClass world;
    
    Raytracer raytracer;
    
    const char fileName[7][20] = {"Suzanne.obj", "circle.obj", "cone.obj", "torus.obj", "cube.obj", "plane.obj", "betterSuzanne.obj"};
    
    raytracer.importObjFile(fileName[6], Vector(-1.1, 1.2, -16), Color(0, 125, 125), SHADED);
    raytracer.importObjFile(fileName[1], Vector(1, -.8, -20), Color(100, 189, 217), SHADED);
    raytracer.importObjFile(fileName[2], Vector(-1.3, -1.4, -20), Color(123, 65, 162), SHADED);
    raytracer.importObjFile(fileName[3], Vector(1.3, 1.2, -12), Color(100, 25, 25), SHADED);
    
    
    
    world.initialize();
    
    uint32_t * pixels = raytracer.render();
    
    world.draw(pixels);
    
    t = clock() - t;
    
    //printf("Rendered in %lu clock ticks\n(%f seconds)\n%f frames per second \n", t, (float)t/CLOCKS_PER_SEC, (float)CLOCKS_PER_SEC/t);
    printf("Rendered in %f seconds.\n", (float)t/CLOCKS_PER_SEC);
    
    while (world.isRunning) {
        world.event();
    }
    
    world.cleanUp();
    
    return 0;
}
