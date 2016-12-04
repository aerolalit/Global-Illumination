//
//  ObjectProperties.hpp
//  Globall_illumination
//
//  Created by ललित सिंह on 02/12/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//
#include "RGBColor.hpp"

#ifndef ObjectProperties_hpp
#define ObjectProperties_hpp

#include <stdio.h>
class OProperties {
public:
    double mirror;  //mirroring constants 0 to 1
    double transparency;  //refraction cosnstants 0 to 1
    double n;  // power for blingphong
    RGBcolor ks;
    RGBcolor kd;
    RGBcolor ka;
};
#endif /* ObjectProperties_hpp */
