//
//  RGBcolor.cpp
//  PI_shadow_mirror
//
//  Created by ललित सिंह on 01/12/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include "RGBcolor.hpp"
RGBcolor::RGBcolor(double x, double y, double z){
    this->R = x;
    this->G = y;
    this->B = z;
}
RGBcolor::RGBcolor (){
    this->R = 0;
    this->G = 0;
    this->B = 0;
}
double RGBcolor::getR(){
    return this->R;
}
double RGBcolor:: getG(){
    return this->G;
}
double RGBcolor:: getB(){
    return this->B;
}
void RGBcolor:: setR(double R){
    this-> R = R;
}
void RGBcolor:: setG(double G){
    this ->G = G;
}
void RGBcolor:: setB(double B){
    this ->B = B;
}

RGBcolor operator * ( double& k , RGBcolor& color){
    RGBcolor result = RGBcolor( k*color.R, k* color.G, k* color.B);
    return result;
}
RGBcolor operator * ( RGBcolor& color, double& k){
    RGBcolor result = RGBcolor( k*color.R, k* color.G, k* color.B);
    return result;
}
RGBcolor operator + ( RGBcolor& a, RGBcolor& b){
    RGBcolor result = RGBcolor( a.R+b.R, a.G+ b.G, a.B + b.G);
    return result;
}
