//
//  Vector.h
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/24/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __NewRaytracer__Vector__
#define __NewRaytracer__Vector__

#include <math.h>
#include <stdio.h>

class Vector {
    
public:
    
    double x, y, z;
    
    Vector()    {x = 0; y = 0; z = 0;}
    
    Vector(double _x, double _y, double _z)  {x = _x; y = _y; z = _z;}
    
    bool operator==(Vector v)   {return (x == v.x) && (y == v.y) && (z = v.z);}
    
    void operator=(Vector v)    {x = v.x; y = v.y; z = v.z;}
    
    void operator+=(Vector v)    {x += v.x; y += v.y; z += v.z;}
    
    Vector operator+(Vector v)  {return Vector((double)(x + v.x), (double)(y + v.y), (double)(z + v.z));}
    
    Vector operator-(Vector v)  {return Vector(x - v.x, y - v.y, z - v.z);}
    
    Vector operator-(double a)   {return Vector(x - a, y - a, z - a);}
    
    void operator+=(double a) {x += a; y += a; z += a;}
    
    Vector operator+(double a)  {return Vector(x + a, y + a, z + a);}
    
    void operator*=(double a) {x *= a; y *= a; z *= a;}
    
    Vector operator*(double a)   {return Vector(x * a, y * a, z * a);}
    
    double dotProduct(Vector v)   {return x * v.x + y * v.y + z * v.z;}
    
    static double dotProduct(Vector a, Vector b) {return (double)(a.x * b.x) + (double)(a.y * b.y) + (double)(a.z * b.z);}
    
    //Vector crossProduct(Vector v)   {return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}
    
    static Vector crossProduct(Vector a, Vector b)  {return Vector((double)(a.y * b.z) - (double)(a.z * b.y), (double)(a.z * b.x) - (double)(a.x * b.z), (double)(a.x * b.y) - (double)(a.y * b.x));}
    
    double mag() {return sqrt((double)(x*x + y*y + z*z));}
    
    double magSqrd() {return x*x + y*y + z*z;}
    
    void normalize()    {*this *= ((double)1 / this->mag());}
    
    void print()    {printf("{%e, %e, %e}\n", x, y, z);}
    
};

#endif /* defined(__NewRaytracer__Vector__) */
