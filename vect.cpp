//
//  Vect.cpp
//  hw3class
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include "vect.hpp"
Vect::Vect(){
    this-> x = 0;
    this-> y = 0;
    this-> z = 0;
}
Vect::Vect(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
Vect:: Vect(mypoint3f point){
    this->x = point.getx();
    this->y = point.gety();
    this->z = point.getz();
}
double Vect:: getx(){
    return this->x;
}
double Vect::gety(){
    return this->y;
}
double Vect::getz(){
    return this->z;
}
Vect:: Vect(mypoint3f startPoint, mypoint3f endPoint){
    this->x = endPoint.getx() - startPoint.getx();
    this->y = endPoint.gety() - startPoint.gety();
    this->z = endPoint.getz() - startPoint.getz();
}
Vect operator * (Vect& u, Vect& v){
    Vect result;      //see at https://en.wikipedia.org/wiki/Cross_product
    result.x = u.y * v.z - u.z * v.y;
    result.y = u.z * v.x - u.x *v.z;
    result.z = u.x * v.y - u.y * v.x;
    return result;
}
Vect operator * (double& t, Vect& v){
    double x = v.getx() *t;
    double y = v.gety() *t;
    double z = v.getz() *t;
    return Vect(mypoint3f(x,y,z));
}
std::ostream& operator <<(std::ostream& out, Vect& a){
    out<<"x:"<<a.getx()<<" y:"<<a.gety()<<" z:"<<a.getz()<<std::endl;
    return out;
}





