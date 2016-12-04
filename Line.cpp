//
//  Line.cpp
//  homework3
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include <stdio.h>
#include "Line.hpp"
//#include "mypoint3f.hpp"

Line::Line(){
    this-> startPoint = mypoint3f();
    this-> endPoint = mypoint3f();
}
Line:: Line(mypoint3f sPoint, mypoint3f ePoint){
    this->startPoint = sPoint;
    this-> endPoint = ePoint;
}
Line:: Line(mypoint3f sPoint, Vect dir){
    this->startPoint = sPoint;
    this-> direction = mypoint3f( dir.getx(), dir.gety(), dir.getz());
}
mypoint3f Line:: getStartPoint(){
    return this-> startPoint;
}
mypoint3f Line:: getEndPoint(){
    return this-> endPoint;
}

