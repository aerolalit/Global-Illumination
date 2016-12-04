//
//  mypoint3f.hpp
//  hw3class
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef mypoint3f_hpp
#define mypoint3f_hpp

#include <stdio.h>
//#include "Header.hpp"
#include <iostream>
//#include "vect.hpp"
class mypoint3f{
private:
    double x;
    double y;
    double z;
    
public:
    mypoint3f();
    mypoint3f(double, double, double);
    double sumOfSquaresOfXYZ();
    double sumXYZ();
    double getx();
    double gety();
    double getz();
   // mypoint3f normalize();
    double magnitude();
    friend mypoint3f operator -(mypoint3f, mypoint3f);
    friend mypoint3f operator *( mypoint3f, mypoint3f);
    friend mypoint3f operator +(mypoint3f, mypoint3f);
    friend mypoint3f operator *(double, mypoint3f);
    friend mypoint3f operator *( mypoint3f, double);
    friend std::ostream& operator <<(std::ostream&, mypoint3f&);
};

#endif /* mypoint3f_hpp */
