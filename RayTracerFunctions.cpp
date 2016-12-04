//
//  RayTracerFunctions.cpp
//  Globall_illumination
//
//  Created by ललित सिंह on 02/12/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include "RayTracerFunctions.hpp"
#include <time.h>
#include <math.h>
double maxx(double a, double b) {return a>b?a:b;}
double attenuation(double r, double c0, double c1, double c2){
    return min( 1, 1/ (c0 + c1* r + c2 * r*r) );
}
mypoint3f randomPointOnSphere(Sphere S){
    
    double randX = pow(-1.0,(rand() % 2 +1)) * (rand() % 100);
    double randY = pow(-1.0,(rand() % 2 +1)) * (rand() % 100);
    double randZ = pow(-1.0,(rand() % 2 +1)) * (rand() % 100);
    mypoint3f randXYZ = mypoint3f(randX, randY, randZ);
    mypoint3f randVector = normalize(randXYZ- S.center);
    mypoint3f temp = S.radius * randVector;
    mypoint3f randPoint = S.center + temp;
    //std::cout<<randPoint;
    return randPoint;
    
}

double shadowChecker(Lights light, intersectionPoint ip, std::vector<Sphere> Objects){
    
    intersectionPoint temp_ip;
    int blockedRaysCount=0;
    double maxBlockade =0;
    for(int i=0; i < Objects.size(); i++){
        blockedRaysCount = 0;
        for (int k=0; k< 10; k++){
            mypoint3f randPointOnLight = randomPointOnSphere(Sphere(light.radius, light.point));
            Line L = Line(ip.point, randPointOnLight );
            temp_ip = Objects[i].shootRay(L);
            if (temp_ip.doesIntersect && temp_ip.t > 0.01){
                blockedRaysCount++;
            }
        }
        //std::cout<<blockedRaysCount<<std::endl;
          double blockade = (double) blockedRaysCount/ 10.0;
        maxBlockade = blockade > maxBlockade ? blockade : maxBlockade;
    }
  
    return (1-maxBlockade);
}

RGBcolor applyBlingPhong(std::vector<Lights> lights ,mypoint3f viewpoint, intersectionPoint ip, std::vector<Sphere> Objects, OProperties Op){
    
    mypoint3f intersecPoint = ip.point;
    mypoint3f normal = ip.normal;
    
    RGBcolor ks = Op.ks;               //specular refleciton cofficient
    RGBcolor kd = Op.kd;      // cofficient of diffused reflection
    RGBcolor ka = Op.ka;     //cofficient of ambient reflection
    // RGBcolor Ia = Op.Ia;      //intensity of ambient reflection
    //RGBcolor Ip = Op.Ip;        //internsity of diffused reflection
    int n = Op.n;               //power
    
    double c0 = 0.0, c1 = 1, c2 = 01; // the constansts for attenuation
    // int n = 100; // power for specular reflection
    
    
    std::vector<mypoint3f> lightvectors;
    std::vector<mypoint3f> halfvectors;
    std::vector<double> distances;   // distance betweeen intersection point and light
    std::vector<double> f_att ;     // attenuation values
    mypoint3f v = normalize( viewpoint- intersecPoint );
    // double c0 = 0.0, c1 = 1, c2 = 01; // the constansts for attenuation
    for( int i = 0 ; i< lights.size(); i++){
        
        lightvectors.push_back( normalize(lights[i].point- intersecPoint));      // vector along the direction of light1 from point of intersection
        halfvectors.push_back(normalize (v + lightvectors[i]));     //half vector of light 1 and viewpoint
        distances.push_back( distance(intersecPoint, lights[i].point));
        f_att.push_back( attenuation(distances[i], c0, c1, c2));
    }
    
    
    double IR = lights[0].Ia.R * ka.R;
    double IG = lights[0].Ia.G * ka.G;
    double IB = lights[0].Ia.B * ka.B;
    srand(time(NULL));
    for( int i=0; i<lights.size(); i++){
        double shadow_intensity = shadowChecker(lights[i], ip, Objects);
        //checks if the light source is occluded by any of the objects
        IR = IR + shadow_intensity * ( lights[i].Ip.R * f_att[i] * ( kd.R * maxx(dotProduct(normal, lights[i].point),0)  + ks.R * pow(  max( dotProduct(halfvectors[i],normal ), 0),  n ) ) );
        IG = IG + shadow_intensity * ( lights[i].Ip.G * f_att[i] * ( kd.G * maxx(dotProduct(normal, lights[i].point),0)  + ks.G * pow(  max( dotProduct(halfvectors[i],normal ), 0),  n ) ) );
        IB = IB + shadow_intensity * ( lights[i].Ip.B * f_att[i] * ( kd.B * maxx(dotProduct(normal, lights[i].point),0)  + ks.B * pow(  max( dotProduct(halfvectors[i],normal ), 0),  n ) ) );
    }
    return RGBcolor(IR, IG, IB);
    
}
Line reflectedRay(Line incidentRay, Line normal){
    mypoint3f iR = normalize( incidentRay.endPoint - incidentRay.startPoint);
    mypoint3f N = normalize( normal.endPoint - normal.startPoint );
    //https://goo.gl/483lzt check the theory here
    
    mypoint3f normalizedRR= normalize( 2.0 * N * dotProduct(iR, N)-iR); // normalized reflected vector
    Line RR (normal.endPoint, normal.endPoint + normalizedRR);
    return RR;
}
Line traceRefractedRay(Line incidentRay, Line normal, double u ){
    //https://goo.gl/OcKpRU see  theory here
    // u is n1/n2 aka. mue
    mypoint3f i = normalize(incidentRay.endPoint - incidentRay.startPoint); //direction of the incident ray
    mypoint3f n = normalize( normal.endPoint - normal .startPoint );   //direction of normal to the surface
    i = normalize( incidentRay.startPoint- incidentRay.endPoint);
    double theta1 = acos(dotProduct(n, i));
    double theta2 = asin(sin(theta1)/u);
    mypoint3f t = u * i + (u * cos(theta1) -cos(theta2) ) * n;
    Line transmittedRay( normal.getEndPoint(), normal.endPoint + t);
    return transmittedRay;
    
}

RGBcolor rayTrace(Line L, int depth, std::vector<Sphere> Objects, std::vector<Lights> lights, std::vector<OProperties> Op){
    RGBcolor surfaceColor, reflectedColor, refractedColor ;
    std::vector<intersectionPoint> intersectedPoints;
    intersectionPoint ip;
    for(int i =0; i< Objects.size(); i++){
        ip = Objects[i].shootRay(L);
        if(ip.doesIntersect){
            ip.whichObject = i;
            intersectedPoints.push_back(ip);
        }
        
    }
    if (intersectedPoints.size() > 0){
        ip = closestPoint(intersectedPoints, L);
        mypoint3f viewPoint = L.getStartPoint();
        surfaceColor= applyBlingPhong(lights, viewPoint, ip,Objects, Op[ip.whichObject]);
        if (( depth > 0) && (Op[ip.whichObject].mirror > 0)){
            Line Normal( Objects[ip.whichObject].getCenter(),  ip.point);   // Normal goes from centre of the sphere through the intersected point ip on the surface of the sphere
            Line RR = reflectedRay(L, Normal);
            reflectedColor = rayTrace(RR, depth -1, Objects, lights, Op);
        }
        if( (depth >0) && (Op[ip.whichObject].transparency > 0)){
            Line Normal(Objects[ip.whichObject].getCenter(),  ip.point);
            double u= 1.5;
            Line refractedRay = traceRefractedRay(L, Normal, u);
            refractedColor = rayTrace(refractedRay, depth -1, Objects, lights, Op);
        }
        double a = Op[ip.whichObject].mirror;
        double b = Op[ip.whichObject].transparency;
        double temp = 1-a-b;
        RGBcolor temp1 =(temp) * surfaceColor;
        RGBcolor temp2 = a * reflectedColor;
        RGBcolor temp3 = b * refractedColor;
        RGBcolor resultantColor =  (temp1 + temp2) ;
        resultantColor = resultantColor + temp3;
        return  resultantColor;
    }
    else {
        
        surfaceColor = RGBcolor();  //give background color[black]
        return surfaceColor;
    }
    
}
