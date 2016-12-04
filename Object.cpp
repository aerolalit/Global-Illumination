//
//  Object.cpp
//  PI_shadow_mirror
//
//  Created by ललित सिंह on 30/11/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include "Object.hpp"



Sphere::Sphere(){
    this->center = mypoint3f();
    this->radius = 0;
}
Sphere::Sphere(double radius, mypoint3f center1){
    this->center = center1;
    this->radius = radius;
}
TriangularMesh::TriangularMesh(){
    
    std::vector <glm::vec3> vertices;
    std::vector <glm::vec2> uvs;
    std::vector <glm::vec3> normals;
    loadOBJ2("bunny.obj", vertices,  normals);
    double theta = M_PI * 90/180;
    rotateOBJ( vertices,  normals, theta);
    std::vector<std::vector<mypoint3f>> triangularMesh = fitObjectInFrustum(vertices,normals);
    this->vertices = triangularMesh[0];
    this-> normals = triangularMesh[1];
}
mypoint3f Sphere::getCenter(){
    return this->center;
}
intersectionPoint Sphere::shootRay(Line L){
    mypoint3f currentPixelPoint = L.getEndPoint();
    mypoint3f viewPoint = L.getStartPoint();
     mypoint3f pixelPointMinusViewPoint = currentPixelPoint - viewPoint;
    // Formula:(X,Y,Z) =  currentPixelPoint(i,j,k) - viewpoint(Vx,Vy,Vz)
    double sumOfSquaresOfViewPoint = viewPoint.sumOfSquaresOfXYZ();
    //(Vx^2+Vy^2+Vz^2)  where(VX, Vy, Vz) are the co-ordinates of viewpoint
    double sumSquaresOfXYZ = pixelPointMinusViewPoint.sumOfSquaresOfXYZ();   //(X^2+Y^2+Z^2)
    //(X^2+Y^2+Z^2)
    struct mypoint3f viewPointTimesXYZ =  pixelPointMinusViewPoint * viewPoint;
    //(Vx*X, Vy*Y, Vz*Z)
    double sumOfviewPointTimesXYZ = viewPointTimesXYZ.sumXYZ();
    //(Vx*X + Vy*Y + Vz*Z)
    mypoint3f product = this->center * viewPoint;
    double sumOfCenterTimesViewPoint = product.sumXYZ();
    //if (h,k,l) is center of circle then above variable represents
    // h*Vx + k*Vy + l*Vz
    double sumSquaresOfHKL = this->center.sumOfSquaresOfXYZ();
    //(h^2+k^2+l^2)
    mypoint3f tempProduct = this->center * pixelPointMinusViewPoint;
    double sumOfCenterTimesXYZ = tempProduct.sumXYZ();
    //(h*X + k*Y + l*Z)
    
    //After deriving the equation for the intersection of sphere and line through the viewpoint and given pixel of the
    //screen..... we can represent it in form of [[[a*t^2 +b*t + c = 0]]
    //where a, b and c has followint values
    // To view the calculation click on the link given below
    // https://www.dropbox.com/s/8evzmszo19bfybo/Code_logic.pdf?dl=0
    double a = sumSquaresOfXYZ;
    double b = 2*(sumOfviewPointTimesXYZ - sumOfCenterTimesXYZ);
    double c = sumOfSquaresOfViewPoint -2* sumOfCenterTimesViewPoint + sumSquaresOfHKL - this->radius;
    // if the ray intersects the sphere then the discriminant of the equation is positive
    //such that we get real point of intersection
    double discriminant = sqr(b) - 4 * a * c;
    double t1 = NULL, t2 = NULL; // roots of the equation a*t^2 + b*t + c = 0
    intersectionPoint myintersectionPoint;
    myintersectionPoint.doesIntersect = false;
    if ( discriminant> 0 ){
        t1 = (-b + sqrt(discriminant))/(2*a);
        t2 = (-b - sqrt(discriminant))/(2*a);
        //if (t1<=6 || t2<=6){ // t=[0,1] is equivalent to [0,2] because the screen is 2 unit farfrom view point
        //Since the viewsight range is maximum up 12 units, the min(t1,t1) should be lesser than 6
       // myintersectionPoint.point = pointSum(viewPoint, scalarProduct(pointDifference(currentPixelPoint, viewPoint), min(t1,t2) ));
        mypoint3f diff = currentPixelPoint - viewPoint;
        double minval = min(t1,t2);
        myintersectionPoint.t = minval;
        mypoint3f scalarP =  minval * diff;
        myintersectionPoint.point = viewPoint + scalarP;
        // intersection point (x,y,z) = (Vx,Vy,Vz) + t* (pix.x -Vx, pix.y-Vy, pix.z -Vz)
        myintersectionPoint.doesIntersect = true;
        myintersectionPoint.normal = normalize(myintersectionPoint.point - this->center);
        //}
    }
    
    return myintersectionPoint;
}

intersectionPoint TriangularMesh::shootRay(Line L){
    
    std::vector<intersectionPoint> intersectedPoints; //this vector records all the t values for each triangular meshes to which the ray intersects
    for (int k = 0 ; k < this->vertices.size();k+=3){
        
        Triangle T = Triangle(this->vertices[k], this->vertices[k+1], this->vertices[k+2]);
        Triangle NT = Triangle(this->normals[k], this->normals[k+1], this->normals[k+2]); //normals
        mypoint3f vp = L.getStartPoint(); // view point
        mypoint3f cp = L.getEndPoint(); // current pixel point
        Vect N = normal(T); // normal to the plane of the triangle
        mypoint3f tp = T.getv1(); // one of the three vertices of triangle or [triangle point]
        
        double tpx = tp.getx(), tpy= tp.gety(), tpz = tp.getz();
        double Nx = N.getx(), Ny = N.gety(), Nz = N.getz();
        double vpx = vp.getx(), vpy = vp.gety(), vpz = vp.getz();   //viewpoint
        double cpx = cp.getx(), cpy = cp.gety(), cpz = cp.getz();   //currentPixelPoint
        
        double num = Nx * (vpx -tpx) + Ny *(vpy-tpy) + Nz *(vpz - tpz);
        double den = Nx *(cpx -vpx) + Ny* (cpy-vpy) + Nz *(cpz - vpz);
        //std::cout<<"num:"<<num<<" den: "<<den<<std::endl;
        intersectionPoint result;
        if (den == 0 ){
            result.doesIntersect = false;
            
        }
        else {
            double temp = -num / den;
            // std::cout<<"t:"<<t<<std::endl;
            
            mypoint3f intsecPoint = findPointOnLine(temp, L);
            //std::cout<<T;
            //std::cout<<intsecPoint<<std::endl;
            bool var = doesPointLiesInsideTriangle(intsecPoint, T);
            result.doesIntersect= var;
            if (result.doesIntersect){
                result.point =intsecPoint;
                result.t = temp;
                mypoint3f BC = barycentricCoordinates(intsecPoint, T);
                mypoint3f temp1 = mypoint3f( NT.getv1().getx() * BC.getx(), NT.getv1().gety() * BC.getx(), NT.getv1().getz() * BC.getx());
                mypoint3f temp2 = mypoint3f( NT.getv2().getx() * BC.gety(), NT.getv2().gety() * BC.gety(), NT.getv2().getz() * BC.gety());
                mypoint3f temp3 = mypoint3f( NT.getv3().getx() * BC.getz(), NT.getv3().gety() * BC.getz(), NT.getv3().getz() * BC.getz());
                mypoint3f sum = temp1 + temp2;
                sum = sum + temp3;
                result.normal = normalize( sum );
                intersectedPoints.push_back(result);
            }
        }
        
    }
    intersectionPoint intersecPoint;
    if(intersectedPoints.size() == 0){
        intersecPoint.doesIntersect = false;
    }
    else{
        intersecPoint = closestPoint(intersectedPoints, L);
        intersecPoint.doesIntersect = true;
    }
    return intersecPoint;
    
}
