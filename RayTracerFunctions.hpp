//
//  RayTracerFunctions.hpp
//  Globall_illumination
//
//  Created by ललित सिंह on 02/12/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef RayTracerFunctions_hpp
#define RayTracerFunctions_hpp

#include <stdio.h>
#include "Header.hpp"
#include "RGBcolor.hpp"
#include "Line.hpp"
#include "Object.hpp"
#include "mypoint3f.hpp"
double max(double, double);
mypoint3f randomPointOnSphere(Sphere S);
double attenuation(double, double, double, double, double);
RGBcolor applyBlingPhong(std::vector<Lights>, mypoint3f, intersectionPoint, std::vector<Sphere>, OProperties);
Line traceRefractedRay(Line incidentRay, Line normal, double u );
Line reflectedRay(Line incidentRay, Line normal);
RGBcolor rayTrace(Line, int, std::vector<Sphere>, std::vector<Lights> lights, std::vector<OProperties> Op);


#endif /* RayTxracerFunctions_hpp */
