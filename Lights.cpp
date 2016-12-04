//
//  Lights.cpp
//  Globall_illumination
//
//  Created by ललित सिंह on 02/12/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include "Lights.hpp"
Lights::Lights(mypoint3f point, double radius, RGBcolor Ia , RGBcolor Ip){
    this-> Ia = Ia;
    this-> Ip = Ip;
    this-> point = point;
    this-> radius = radius;
}
