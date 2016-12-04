//
//  Header.h
//  hw22
//
//  Created by ललित सिंह on 24/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <vector>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "glm.hpp"
#include "vect.hpp"
#include "mypoint3f.hpp"
#include "Triangle.hpp"
#include "Line.hpp"
#include "RGBcolor.hpp"
#include "ObjectProperties.hpp"
#include "Lights.hpp"
//#include "Object.hpp"
struct intersectionPoint{
    double t;
    mypoint3f point;
    mypoint3f normal;
    int whichObject;
    bool doesIntersect;
};
double avg(std::vector<double>);
double sqr(double);
double map(double, double, double, double, double);
double min_t(std::vector<double>);
double min(double, double);
double dotProduct(mypoint3f , mypoint3f);
double distance (mypoint3f, mypoint3f);
mypoint3f normalize(mypoint3f);
std::vector<std::vector<mypoint3f>> fitObjectInFrustum(std::vector<glm::vec3>, std::vector<glm::vec3>);
intersectionPoint closestPointToViewPoint ( mypoint3f, std::vector<intersectionPoint>);
intersectionPoint closestPoint(std::vector<intersectionPoint>, Line);
mypoint3f barycentricCoordinates(mypoint3f, Triangle);
mypoint3f findPointOnLine(double , Line);
double determinant( mypoint3f, mypoint3f, mypoint3f);
bool doesPointLiesInsideTriangle(mypoint3f , Triangle);

Vect normal(Triangle );
bool rotateOBJ(std::vector<glm::vec3> & vertices, std::vector<glm::vec3> normals, double theta);
intersectionPoint doesRayIntersectsTriangle( Triangle T,  Line L);

bool loadOBJ(
             const char * path,
             std::vector<glm::vec3> & out_vertices,
             std::vector<glm::vec3> & out_normals
             );

bool loadOBJ2(
             const char * path,
             std::vector<glm::vec3> & out_vertices,
             std::vector<glm::vec3> & out_normals
             );


bool loadAssImp(
                const char * path,
                std::vector<unsigned short> & indices,
                std::vector<glm::vec3> & vertices,
                std::vector<glm::vec3> & normals
                );
#endif /* Header_h */
