//
//  Raytracer.cpp
//  NewRaytracer
//
//  Created by Ellis Sparky Hoag on 2/24/15.
//  Copyright (c) 2015 Ellis Sparky Hoag. All rights reserved.
//


#include "Raytracer.h"
#include "Definitions.h"


/*
 *  X-Axis is to the right
 *  Y-Axis is up
 *  Z-Axis is out of the screen
 */

Raytracer::Raytracer()  {
    
    pixelWidth = WWIDTH;
    
    pixelHeight = WHEIGHT;
    
    pixelBuffer = new uint32_t[WWIDTH * WHEIGHT];
    
    eye.width = 1;
    eye.height = 1;
    eye.nearClip = -3;
    eye.location = Vector(0, 0, 0);
    //eye.direction = Vector(0, 0, -1);
    //eye.direction.normalize();
    
    //numTriangles = 0;
    
    //numLights = 0;
    
    addTriangle(Vector(0.1, -1.1, -18), Vector(-0.9, 0, -20), Vector(-0.9, -1, -20), Color(0, 255, 0), SHADED);
    
    addTriangle(Vector(-10, -10, -25), Vector(10, -10, -25), Vector(0, 10, -25), Color(0, 0, 200), SHADED);
    
    addLight(Vector(10, 1, 0), Color(255, 255, 255), .6);
    
    addLight(Vector(-1, -1, 0), Color(0, 0, 0), .9);
    
    ambientLight = 0;
    
}

uint32_t * Raytracer::render()   {
    
    /*
     *  For all pixels
     *      get the first Ray
     *      trace it to first intersection and return color
     */
    
    for (int i = 0; i < pixelWidth; i++) {
        for (int j = 0; j < pixelHeight; j++) {
            
            Ray r = getFirstRay(i, j);
            
            Color c = traceRay(r, 0);
            
            pixelBuffer[i + j * pixelWidth] = c.bits;
            //printf("i = %d, j = %d\n", i, j);
        }
        //printf("i = %d\n", i);
    }
    
    return pixelBuffer;
}

Color Raytracer::traceRay(Ray r, int depth) {
    
    /*
     *  Get point of first intersection
     *  calculate color of that point
     */
    
    Vector point;
    
    int triangleID = getFirstIntersection(&r, &point);
    
    if  (triangleID == -1)  {
        return Color(0, 0, 0);
    }
    else if  (triangles[triangleID].shadeType == SOLID)  {
        return triangles[triangleID].color;
    }
    else if     (triangles[triangleID].shadeType == SHADED) {
        Color c = triangles[triangleID].color * (ambientLight + diffuseLight(point, triangleID));
        /*if (c.bits == 0) {
            //c.print();
            point.print();
        }*/
        return c;
    }
    return Color(0, 0, 0);
}

Ray Raytracer::getFirstRay(int column, int row) {
    
    Ray r;
    
    double widthSeg = eye.width / pixelWidth;
    double heightSeg = eye.height / pixelHeight;
    
    //double xOffSet = pixelWidth % 2 == 0 ? 1.f/2.f : 0;
    //double yOffSet = pixelHeight % 2 == 0 ? 1.f/2.f : 0;
    
    r.position.x = (double)widthSeg * floor(column - (pixelWidth/2.f));
    r.position.y = (double)heightSeg * floor((pixelHeight/2.f) - row);
    r.position.z = eye.nearClip;
    
    /*
    //No camera rotations
    
    //Vector toCell = r.position - Vector(0, 0, eye.nearClip);
    
    //Vector cameraCenter = eye.direction * r.position.mag();
    
    //r.position = cameraCenter + toCell;
    
    //r.position += eye.location;
    
    //r.direction = eye.direction;
   // r.direction += r.position - eye.location - Vector(0, 0, eye.nearClip);
    //r.direction.normalize();
     */
    
    r.direction = r.position;
    r.direction.normalize();
    
    r.position += eye.location;
    
    return r;
}

void Triangle::calcTraingle()   {
    
    normal = Vector::crossProduct(p2 - p1, p3 - p1);
    
    normal.normalize();
    
    d = Vector::dotProduct(normal, p1);
}

void Raytracer::addTriangle(Vector a, Vector b, Vector c, Color d, int s)  {
    
    triangles.push_back(Triangle(a, b, c, d, s));
        
    /*Triangle * tmpTriangles = new Triangle[++numTriangles];
    
    for (int i = 0; i < numTriangles - 1; i++) {
        tmpTriangles[i] = triangles[i];
    }
    
    Triangle t(a, b, c, d, s);
    
    tmpTriangles[numTriangles - 1] = t;
    
    triangles = new Triangle[numTriangles];
    
    for (int i = 0; i < numTriangles; i++) {
        triangles[i] = tmpTriangles[i];
    }*/
}

void Raytracer::addLight(Vector l, Color c, double i)  {
    
    Light tmp;
    
    tmp.location = l;
    tmp.color = c;
    tmp.intensity = i;
    
    lights.push_back(tmp);
    
    /*Light * tmpLights = new Light[++numLights];
    
    for (int i = 0; i < numLights - 1; i++) {
        tmpLights[i] = lights[i];
    }
    
    Light b;
    
    b.location = l;
    b.color = c;
    b.intensity = i;
    
    tmpLights[numLights - 1] = b;
    
    lights = new Light[numLights];
    
    for (int i = 0; i < numLights; i++) {
        lights[i] = tmpLights[i];
    }*/
}

int Raytracer::getFirstIntersection(Ray * r, Vector * p)   {
    
    /*
     *  For each triangle
     *      if my ray is not parallel
     *          if my ray intersects
     *              if closest then note point
     */
    
    Vector intersectionPoint;
    
    int triangleNumber = -1;
    
    double closest = INFINITY;
    
    for (int i = 0; i < triangles.size(); i++) {
        
        double x = Vector::dotProduct(r->direction, triangles[i].normal);
        
        
        if  (x < 0) {
            
            //my triangle is not parallel to my ray so i test for intersection
            //I also want to make sure that the triangle is facing towards the ray. The triangle normal needs point in the opposite direction as my ray. So x needs to be negative.
            
            double t = (triangles[i].d - Vector::dotProduct(triangles[i].normal, r->position)) / x;
            
            if(t > std::numeric_limits<double>::epsilon())   {
                //make sure that the intersection is in the direction of the ray also make sure it goes past its origin
                
                intersectionPoint = r->position + r->direction * t;
                
                if (Vector::dotProduct(Vector::crossProduct((triangles[i].p2 - triangles[i].p1), (intersectionPoint - triangles[i].p1)), triangles[i].normal) >= -1 * std::numeric_limits<double>::epsilon()) {
                    
                    if (Vector::dotProduct(Vector::crossProduct((triangles[i].p3 - triangles[i].p2), (intersectionPoint - triangles[i].p2)), triangles[i].normal) >= -1 * std::numeric_limits<double>::epsilon()) {
                        
                        if (Vector::dotProduct(Vector::crossProduct((triangles[i].p1 - triangles[i].p3), (intersectionPoint - triangles[i].p3)), triangles[i].normal) >= -1 * std::numeric_limits<double>::epsilon()) {
                            
                            //I use epsilon because comparing type double to zero is very bad.
                            //I know I should scale epsilon to the number I'm comparing but I honestly don't know enough to do this.
                            
                            /*
                             *      Sometimes if my light ray is lined up perfectly with an edge of two triangles
                             *  then the ray will collide with the other triangle. This is important because when
                             *  I try to test if there is a triangle in the way of my light source for a given point
                             *  then it will be wrong. So there may be a fine pixelated line of shadow where there shouldn't be
                             */
                            
                            if (closest > t)  {
                                if (p != nullptr) {
                                    *p = intersectionPoint;
                                }
                                closest = t;
                                triangleNumber = i;
                            }
                        }
                    }
                }
            }
        }
    }
    return triangleNumber;
}

double Raytracer::diffuseLight(Vector p, int ID) {
    
    double diffuse, totalDiffuse = 0;
    
    for (int i = 0; i < lights.size(); i++) {
        
        Vector lightDirection = lights[i].location - p;
        lightDirection.normalize();
        
        Ray lightRay;
        lightRay.direction = lightDirection * -1;    //I need my light vector to point in the opposite direction of my potencial triangle normal vector
        lightRay.position = lights[i].location;
        
        int lightBlockingTriangle = getFirstIntersection(&lightRay, nullptr);
        
        
        if(lightBlockingTriangle == ID || lightBlockingTriangle == -1)   {
            //there is no triangle in the way of the light source
            
            //lightDirection.normalize();
            
            diffuse = lights[i].intensity * Vector::dotProduct(triangles[ID].normal, lightDirection) / lightDirection.magSqrd();
            
            totalDiffuse += (diffuse > 0) ? diffuse : 0;
        }
    }
    
    totalDiffuse = (totalDiffuse > 1) ? 1 : totalDiffuse;
    
    return totalDiffuse;
}


bool Raytracer::addMesh(const std::vector<Vector> & vertices, const std::vector<int> & indices, Color d, int s)    {
        
    for (int i = 0; i < indices.size(); i += 3) {
        if (indices[i] <= vertices.size()) {
            addTriangle(vertices[indices[i]-1], vertices[indices[i+1]-1], vertices[indices[i+2]-1], d, s);
        }
        else    {
            printf("ERROR: indice = %d\n", indices[i]);
            return false;
        }
        //printf("{%d, %d, %d}\n", indices[i], indices[i+1], indices[i+2]);
    }
    
    //printf("Triangles: %u\n", triangles.size());
    
    return true;
}

bool Raytracer::importObjFile(const char path[], Vector location, Color c, int shadeType)  {
    
    std::vector<Vector> vertices;
    
    std::vector<int> indices;
    
    FILE * dataFile = fopen(path, "r");
    
    if (dataFile == nullptr) {
        printf("Failure to open file!");
        return false;
    }
    
    char * buffer = new char[100];  //each line is probably less than 100
    
    while   (fgets(buffer, 100, dataFile) != nullptr)    {
        //I have gotten a new line
        
        if (buffer[0] == 'v') {
            //this line represents a vertice
            
            char * first = strchr(buffer, ' ');
            char * second = strchr(first+1, ' ');
            char * third = strchr(second+1, ' ');
            
            Vector tmp = location + Vector(atof(first), atof(second), atof(third));
            
            vertices.push_back(tmp);
            
            //vertices.back().print();
        }
        else if (buffer[0] == 'f')  {
            //this line represents an indice
            
            char * first = strchr(buffer, ' ');
            char * second = strchr(first+1, ' ');
            char * third = strchr(second+1, ' ');
            
            
            indices.push_back(atoi(first));
            indices.push_back(atoi(second));
            indices.push_back(atoi(third));
            //printf("{%d, %d, %d}\n", atoi(first), atoi(second), atoi(third));
        }
    }
    
    return addMesh(vertices, indices, c, shadeType);
}

bool Raytracer::doubleAlmostEqual(double a, double b, int maxUlpsDiff)   {
    
    double difference = fabs(a - b);
    
    if (difference < std::numeric_limits<double>::epsilon()) {
        return true;
    }
    
    if (signbit(a) != signbit(b)) {
        //different signes are not equal but maybe 0 == -0
        if (a == b) {
            return true;
        }
        return false;
    }
    
    int expA, expB;
    
    double significandA = frexp(a, &expA);
    
    double significandB = frexp(b, &expB);
    
    uint32_t rawMantissaA = significandA * pow(FLT_RADIX, DBL_MANT_DIG);
    
    uint32_t rawMantissaB = significandB * pow(FLT_RADIX, DBL_MANT_DIG);
    
    uint32_t ulpsDiff = abs(rawMantissaA - rawMantissaB);
    
    if (ulpsDiff <= maxUlpsDiff) {
        //printf("%u", ulpsDiff);
        return true;
    }
    
    return false;
}
