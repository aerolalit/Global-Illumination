//
//  Lights.hpp
//  Globall_illumination
//
//  Created by ललित सिंह on 02/12/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef Lights_hpp
#define Lights_hpp

#include <stdio.h>
#include "mypoint3f.hpp"
#include "RGBcolor.hpp"
class Lights{
public:
    mypoint3f point;
    double radius;
    RGBcolor Ia;
    RGBcolor Ip;
    Lights(mypoint3f, double, RGBcolor, RGBcolor);
};
#endif /* Lights_hpp */
