//
//  main.cpp
//  hw3
//
//  Created by ललित सिंह on 24/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//


#include <iostream>
#include <math.h>
#include <fstream>
#include "glm.hpp"  //  documentation at https://glm.g-truc.net
#include "Header.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "Line.hpp"
#include "mypoint3f.hpp"
#include "sphere.hpp"
#include "Triangle.hpp"
#include "vect.hpp"
#include <vector>
#include "Object.hpp"
#include "ObjectProperties.hpp"
#include "RayTracerFunctions.hpp"
#include "Lights.hpp"
using namespace std;
/*
int main (){
    Line  V(mypoint3f(3,3,0),mypoint3f(1,1,0));
    Line N(mypoint3f(-1,1,0), mypoint3f(1,1,0));
    Line RR = reflectedRay(N,N);
    cout<<"start: "<<RR.startPoint<<" E: "<<RR.endPoint<<endl;
}
*/
int main( int argc, const char * argv[]){
    
    mypoint3f viewPoint = mypoint3f(0,0,-2);
    
    vector<Sphere> myObjects;
    vector <OProperties> ObjectProperties;
    vector<Lights> lights;

    //TriangularMesh TM;
    Sphere S1(1.2, mypoint3f(0, 0.8, 3));
    Sphere S2(1.2, mypoint3f(-0.89, -0.89, 4));
    Sphere S3(0.25, mypoint3f(0,0, 2));
    
    
    myObjects.push_back(S1);
    myObjects.push_back(S2);
    myObjects.push_back(S3);
    
    OProperties Op1, Op2,Op3;
    Op1.ks = RGBcolor(1,1,1);               //specular refleciton cofficient
    Op1.kd = RGBcolor(0.7, 0.7, 0.7);       // cofficient of diffused reflection
    Op1.ka = RGBcolor(0.1, 0.0, 1.0);       //cofficient of ambient reflection
    Op1.n = 10;
    Op1.mirror = 0.0;
    Op1.transparency = 0.0;
    
    Op2.ks = RGBcolor(1,1,1);               //specular refleciton cofficient
    Op2.kd = RGBcolor(0.9, 0.9, 0.9);       // cofficient of diffused reflection
    Op2.ka = RGBcolor(0.0, 0.1, 0.6);       //cofficient of ambient reflection
    Op2.n = 10;
    Op2.mirror = 0.5;
    Op2.transparency = 0;
    
    Op3.ks = RGBcolor(1,1,1);               //specular refleciton cofficient
    Op3.kd = RGBcolor(1, 0.5, 0.7);       // cofficient of diffused reflection
    Op3.ka = RGBcolor(0.1, 0.1, 0.1);       //cofficient of ambient reflection
    Op3.n = 100;
    Op3.mirror = 0.0;
    Op3.transparency = 0.5;
    
    //Lights::Lights(mypoint3f point, double radius, RGBcolor Ia , RGBcolor Ip)
    //lights.push_back( Lights( mypoint3f(0, 6, 5.0),0.1, RGBcolor(1, 1, 1),RGBcolor(1, 1, 1))) ;
    lights.push_back( Lights( mypoint3f(+2,2,-2),0.1, RGBcolor(1,1,1),RGBcolor(1, 1, 1) ) );
    lights.push_back(Lights( mypoint3f(-6,-6,6),0.1, RGBcolor(1,1,1),RGBcolor(1, 1, 1) ));
   // lights.push_back(Lights( viewPoint,0.1, RGBcolor(1,1,1),RGBcolor(1, 1, 1) ));
  
    
    ObjectProperties.push_back(Op1);
    ObjectProperties.push_back(Op2);
    ObjectProperties.push_back(Op3);
    
    // try loadOBJ() function for if you get parser problem
    
    // The triangular meshes are loaded in <vector> vertices
    
    int i,j;
    int N = 500;   //change resolution here
    //the resolution will be N*N
    double increment = 2.0/(2*N);
    //mypoint3f lightPoint1 = mypoint3f(0, 6, 5.0);   //location of the source of the light source 1
   // mypoint3f lightPoint2 = mypoint3f(-4, -4, 2.0);   //location of the source of the light source 1
   
                         //visit this link for my code logic https://www.dropbox.com/s/v6m2b3rnzlxjn2u/Code_logic_3.pdf?dl=0
   
    
    std::ofstream ofs("./image.ppm", std::ios::out | std::ios::binary);
        ofs << "P6\n" << 2*N << " " << 2*N << "\n255\n";
        for(i = 0; i< 2*N; i++)
        {
            for( j = 0; j < 2*N; j ++)
            {
                mypoint3f currentPixelPoint = mypoint3f(-1.0 + ((double)i + 0.5)*increment, 1.0 - ((double)j + 0.5)*increment, 0.0);
                
                Line L = Line(viewPoint, currentPixelPoint);
                int depth = 6;
                RGBcolor color = rayTrace(L, depth, myObjects, lights, ObjectProperties);
                 ofs << (unsigned char) (color.getR() * 555) << (unsigned char)(color.getG() *555) << (unsigned char)(color.getB()*555);
                //cout<<color.getR()*255<<" "<<color.getG()*255<<" "<<color.getB()*255<<endl;
                
 
        }
        cout<<endl;
    }
        
        ofs.close();
        
    return 0;
}
