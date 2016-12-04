//
//  mypoint3f.cpp
//  hw3class
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//
//#include "header.hpp"
#include "mypoint3f.hpp"
#include <cmath>
/*double sqr(double a){
return a *a;
}*/
mypoint3f::mypoint3f(){
    this->x = 0;
    this->y = 0 ;
    this->z = 0;
    
}
mypoint3f::mypoint3f(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
double mypoint3f::getx(){
    return this->x;
}
double mypoint3f::gety(){
    return this->y;
}
double mypoint3f::getz(){
    return this->z;
}
/*
mypoint3f mypoint3f::normalize(){
    double magnitude = sqrt(sqr(this->x) + sqr(this -> y) + sqr(this-> z) );
    mypoint3f result;
    result.x = this->x / magnitude;
    result.y = this->y / magnitude;
    result.z = this->z / magnitude;
    return result;
}
 */
double mypoint3f::magnitude(){
    return sqrt((this->x) * this->x + (this->y) * this->y + (this->z)* this->z) ;
}

double mypoint3f:: sumOfSquaresOfXYZ(){
    return ((this->x)*(this->x) +  this->y * this->y + this->z * this->z);
}
double mypoint3f:: sumXYZ(){
    return (this->x + this->y + this->z);
}
mypoint3f operator - (mypoint3f a, mypoint3f b){
    mypoint3f result = mypoint3f(a.x - b.x, a.y -b.y, a.z - b.z);
    return result ;
}
mypoint3f operator *(mypoint3f a, mypoint3f b){
    mypoint3f result = mypoint3f(a.x * b.x, a.y *b.y, a.z * b.z);
    return result ;
}
mypoint3f operator *(double k, mypoint3f a){
    mypoint3f result = mypoint3f(a.x * k, a.y * k, a.z * k);
    return result;
}

mypoint3f operator *(mypoint3f a, double k){
    mypoint3f result = mypoint3f(a.x * k, a.y * k, a.z * k);
    return result;
}
mypoint3f operator + (mypoint3f a, mypoint3f b){
    mypoint3f result = mypoint3f(a.x + b.x, a.y + b.y, a.z + b.z);
    return result;
}
std::ostream& operator <<(std::ostream& out, mypoint3f& a){
    out<<"x:"<<a.getx()<<" y:"<<a.gety()<<" z:"<<a.getz()<<std::endl;
    return out;
}










