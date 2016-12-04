//
//  Vector.hpp
//  hw3class
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include "mypoint3f.hpp"
#include <iostream>
class Vect{
private:
    double x;
    double y;
    double z;
public:
    Vect();
    Vect(double, double, double);
    Vect(mypoint3f, mypoint3f);
    Vect(mypoint3f);
    double getx();
    double gety();
    double getz();
    friend Vect operator *(double&, Vect&);
    friend Vect operator *(Vect&, Vect&);//crossproduct
    friend std::ostream& operator <<(std::ostream&, Vect&);

    
};
#endif /* Vector_hpp */
