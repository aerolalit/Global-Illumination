//
//  Object.hpp
//  PI_shadow_mirror
//
//  Created by ललित सिंह on 30/11/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include "mypoint3f.hpp"
#include "Line.hpp"
#include "vect.hpp"
#include "Header.hpp"
#include <vector>
#include "glm.hpp"
class Object {
public:
     intersectionPoint shootRay(Line);
};

class Sphere: public Object{
private:
    
public:
    mypoint3f center;
    double radius;
    Sphere();
    Sphere(double, mypoint3f);
    mypoint3f getCenter();
    intersectionPoint shootRay(Line);
};

class TriangularMesh: public Object{
private:
    std::vector<mypoint3f> vertices;
    std::vector<mypoint3f> normals;
public:
    intersectionPoint shootRay(Line);
    TriangularMesh();
    
};
#endif /* Object_hpp */
