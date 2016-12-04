//
//  Line.hpp
//  homework3
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef Line_h
#define Line_h
#include "mypoint3f.hpp"
#include "vect.hpp"
class Line{
    private:
    
    public:
    Line();
    mypoint3f startPoint;
    mypoint3f endPoint;
    mypoint3f direction;
    mypoint3f getStartPoint();
    mypoint3f getEndPoint();
    Line(mypoint3f, mypoint3f);
    Line(mypoint3f, Vect);
    
};

#endif /* Line_h */
