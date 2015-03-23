//
//  Color.h
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/23/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//

#ifndef NewRaytracer_Color_h
#define NewRaytracer_Color_h

#include <stdlib.h>

class Color {
    
public:
    
    uint32_t bits;
    
    Color() {
        bits = 0;
    }
    
    Color(uint8_t r, uint8_t g, uint8_t b)  {
        bits = ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
    }
    
    void getSpectrum(uint8_t * r, uint8_t * g, uint8_t * b);
    
    void operator=(Color c)   {
        bits = c.bits;
    }
    
    Color operator*(double a);
    
    void print();
    
};

#endif
