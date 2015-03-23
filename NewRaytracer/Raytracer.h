//
//  Raytracer.h
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/24/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __NewRaytracer__Raytracer__
#define __NewRaytracer__Raytracer__

#include "Color.h"
#include "Vector.h"

#include <stdlib.h>
#include <string>
#include <vector>
#include <float.h>

enum    {
    SOLID = 0,
    SHADED
};

struct Ray {
    Vector position;
    
    Vector direction;
};

struct Frustum  {
    
    double width;
    
    double height;
    
    double nearClip;
    
    Vector location;
    
    Vector direction;
};

class Triangle {
    
public:
    
    Triangle()  {};
    
    Triangle(Vector _a, Vector _b, Vector _c, Color _color, int _s)  {p1 = _a; p2 = _b; p3 = _c; color = _color; calcTraingle(); shadeType = _s;}
    
    Vector p1, p2, p3;
    
    Vector normal;
    
    double d;
    
    Color color;
    
    void calcTraingle();
    
    int shadeType;
    
};

struct  Light   {
    
    Vector location;
    
    double intensity;
    
    Color color;
};

class Raytracer {
    
    int pixelWidth, pixelHeight;
    
    uint32_t * pixelBuffer;
    
    Frustum eye;
    
    std::vector<Triangle> triangles;
    
    std::vector<Light> lights;
    
    //Triangle * triangles;
    
    //Light * lights;
    
    //int numTriangles;
    
    //int numLights;
    
    Color traceRay(Ray r, int depth);
    
    Ray getFirstRay(int column, int row);
    
    int getFirstIntersection(Ray * r, Vector * p);
    
    double diffuseLight(Vector p, int ID);
    
    bool doubleAlmostEqual(double a, double b, int maxUlpsDiff);

public:
    
    Raytracer();
    
    uint32_t * render();
    
    void addTriangle(Vector a, Vector b, Vector c, Color d, int s);
    
    bool addMesh(const std::vector<Vector> & vertices, const std::vector<int> & indices, Color d, int s);
    
    void addLight(Vector l, Color c, double i);
    
    double ambientLight;
    
    bool importObjFile(const char path[], Vector location, Color c, int shadeType);
};

#endif /* defined(__NewRaytracer__Raytracer__) */
