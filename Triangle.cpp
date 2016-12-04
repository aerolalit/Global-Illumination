//
//  triangle.cpp
//  hw3class
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include "Triangle.hpp"

Triangle::Triangle(){
    this->v1 = mypoint3f();
    this->v2 = mypoint3f();
    this->v3 = mypoint3f();
}
Triangle:: Triangle(mypoint3f v1, mypoint3f v2, mypoint3f v3){
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}
mypoint3f Triangle::getv1(){
    return this->v1;
}
mypoint3f Triangle::getv2(){
    return this-> v2;
}
mypoint3f Triangle::getv3(){
    return this -> v3;
}
std::ostream& operator <<(std::ostream& out, Triangle& T){
    std::cout<<"Triangle"<<std::endl;
    out<<T.v1;
    out<<T.v2;
    out<<T.v3;
    return out;
}
