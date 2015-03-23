//
//  Color.cpp
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/24/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//

#include "Color.h"
#include <stdio.h>

void Color::getSpectrum(uint8_t * r, uint8_t * g, uint8_t * b)  {
    
    *r = 0xFF & (bits >> 16);
    
    *g = 0xFF & (bits >> 8);
    
    *b = 0xFF & bits;
}

Color Color::operator*(double a) {
    uint8_t r, g, b;
    
    a = a > 1 ? 1 : a;
    
    getSpectrum(&r, &g, &b);
    
    return Color(r * a, g * a, b * a);
}

void Color::print() {
    uint8_t r, g, b;
    
    getSpectrum(&r, &g, &b);
    
    printf("{%d, %d, %d}\n", r, g, b);

}