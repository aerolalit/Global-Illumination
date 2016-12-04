//
//  RGBcolor.hpp
//  PI_shadow_mirror
//
//  Created by ललित सिंह on 01/12/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef RGBcolor_hpp
#define RGBcolor_hpp

#include <stdio.h>
class RGBcolor {
public:
    double R;
    double G;
    double B;
    RGBcolor();
    RGBcolor(double, double, double);
    double getR();
    double getG();
    double getB();
    void setR(double);
    void setG(double);
    void setB(double);
    friend RGBcolor operator *(RGBcolor&, double&);
    friend RGBcolor operator *(double&, RGBcolor&);
    friend RGBcolor operator +( RGBcolor&, RGBcolor&);
};

#endif /* RGBcolor_hpp */
