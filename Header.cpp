//
//  Header.cpp
//  hw22
//
//  Created by ललित सिंह on 24/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#include "Header.hpp"
#include <math.h>
#include <string>
#include <string.h>
#include <math.h>

#include <vector>
#include <iostream>
double min( double a, double b){
    return a<b?a:b;
}
double max( double a, double b){
    return a>b?a:b;
}
double avg(std::vector<double> tees){
    double avg=0;
    for(int i = 0; i<tees.size() ; i++){
        avg =avg+tees[i];
    }
    return avg/(tees.size()+1);
}

double sqr(double a){
    return a*a;
}
double distance(mypoint3f a, mypoint3f b){
    return sqrt( sqr(a.getx()-b.getx()) + sqr(a.gety()-b.gety()) + sqr(a.getz()-b.getz()));
}
mypoint3f normalize( mypoint3f v){
    double magnitude = v.magnitude();
    double x = v.getx() / magnitude;
    double y = v.gety() / magnitude;
    double z = v.getz() / magnitude;
    return mypoint3f(x,y,z);
}
double dotProduct(mypoint3f v1, mypoint3f v2){
    double result = v1.getx() * v2.getx() + v1.gety() * v2.gety() + v1.getz()* v2.getz();
    return result;
}




double map(double val, double from_min, double from_max, double to_min, double to_max){
    double mapped_val = (val - from_min)/(from_max - from_min) * ( to_max - to_min) + to_min;
    std::cout<<val<<" "<<from_min<<" "<<from_max<<" "<< to_min<<" "<<to_max<<std::endl;
    //std::cout<<mapped_val;
    return mapped_val;
}
double min_t(std::vector<double> vec_t){
    double mint=vec_t[0];
    for(int i = 1; i< vec_t.size(); i++){
        if(mint>vec_t[i]){
            mint= vec_t[i];
        }
    }
    return mint;
}
intersectionPoint closestPointToViewPoint(mypoint3f viewPoint, std::vector<intersectionPoint> vertices){
    double mindist = distance(viewPoint, vertices[0].point);
    int port = 0; // to track where, in the vector, the closest point lies
    for (int i=1; i<vertices.size(); i++){
        if (mindist > distance(viewPoint, vertices[i].point)){
            mindist = distance(viewPoint, vertices[i].point);
            port = i;
        }
    }
    return vertices[port];
}

intersectionPoint closestPoint(std::vector<intersectionPoint> ips, Line L){
    double t;
    double mint=123432343;
    int slot=0;
    for (int i=0; i<ips.size(); i++){
        if(ips[i].t<mint){
            mint = ips[i].t;
            slot = i;
        }
    }
    intersectionPoint result= ips[slot];
    //result.point = findPointOnLine(ips[slot].t, L);
   // result.normal =ips[slot].normal;
    return result;
}
std::vector<std::vector<mypoint3f>> fitObjectInFrustum(std::vector<glm::vec3>vertices, std::vector<glm::vec3> normals){
    
    double minX =vertices[0].x,
    maxX =vertices[0].x,
    minY = vertices[0].y,    // min and max stores the minimum and maximum value in respective coordinares
    maxY = vertices[0].y,     // we will use it for normalization
    minZ = vertices[0].z,
    maxZ = vertices[0].z;
    for ( int i = 0; i < vertices.size(); i+=1){
        if (vertices[i].x > maxX)
            maxX = vertices[i].x;
        if (vertices[i].x < minX)
            minX = vertices[i].x;
        if (vertices[i].y > maxY)
            maxY = vertices[i].y;
        if (vertices[i].y <minY)
            minY = vertices[i].y;
        if (vertices[i].z > maxZ)
            maxZ = vertices[i].z;
        if (vertices[i].z <minZ)
            minZ = vertices[i].z;
        
        
        //  cout<<"x="<<vertices[i].x<<" y=" <<vertices[i].y<<" z=" <<vertices[i].z<<endl;
    }
    // cout<<"minx="<<minX<<" miny=" <<minZ<<" minz=" <<minZ<<endl;
    //cout<<"maxx="<<maxX<<" maxy=" <<maxZ<<" maxz=" <<maxZ<<endl;
    
    std::vector<mypoint3f> myvertices;
    std::vector<mypoint3f> mynormals;
    myvertices.resize(vertices.size());
    mynormals .resize(vertices.size());
    
    //cout<<myvertices.size();
    for(int i = 0; i < vertices.size(); i++){
        double z =((vertices[i].z -minZ) / (maxZ-minZ) * (10-4)) +4;
        double y = (vertices[i].y -minY) / (maxY-minY) *(3-(-3)) -3;
        double x = (vertices[i].x -minX) / (maxX-minX) *(3-(-3)) -3;
        
        double nx= normals[i].x / ( (3+3)/(maxX-minX) );
        double ny= normals[i].y / ( (3+3)/(maxY - minY)  );     //  Normal/scaling
        double nz= normals[i].z / ( (10-4)/(maxZ - minZ)  );
        
        myvertices[i] = mypoint3f(x,y,z);
        mynormals[i] = mypoint3f(nx,ny,nz);
        
        // here we are scaling the object file in a cube with (min, max): X (4,10),Y(-3,3), Z(-3,3)
    }
    std::vector<std::vector<mypoint3f>> triangularMesh;
    triangularMesh.resize(2);
    triangularMesh[0] = myvertices;
    triangularMesh[1] = mynormals;
    return triangularMesh;
    
}

mypoint3f findPointOnLine(double t, Line L){
    mypoint3f vp = L.getStartPoint();
    mypoint3f cp = L.getEndPoint();
    Vect rayDirec = Vect(vp,cp);
    Vect ray = t* rayDirec;
    double x = vp.getx() + ray.getx();
    double y = vp.gety() + ray.gety();
    double z = vp.getz() + ray.getz();
    mypoint3f result= mypoint3f(x,y,z);
    return result;
}
double determinant( mypoint3f p1, mypoint3f p2, mypoint3f p3){
    double a = p1.getx();
    double b = p2.getx();
    double c = p3.getx();
    double d = p1.gety();  // Reference at
    double e = p2.gety(); // https://en.wikipedia.org/wiki/Determinant
    double f = p3.gety();
    double g = p1.getz();
    double h = p2.getz();
    double i = p3.getz();
    double determinant = a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h;
    return determinant;
}
Vect normal(Triangle t){
    Vect vec1 = Vect(t.getv1() , t.getv2());
    Vect vec2 = Vect(t.getv1() , t.getv3());
    return vec1 * vec2;
}
intersectionPoint doesRayIntersectsTriangle(Triangle T, Line L){
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
        return result;

    }
    double t = -num / den;
   // std::cout<<"t:"<<t<<std::endl;
    mypoint3f intsecPoint = findPointOnLine(t, L);
    //std::cout<<T;
    //std::cout<<intsecPoint<<std::endl;
   bool var = doesPointLiesInsideTriangle(intsecPoint, T);
    result.doesIntersect= var;
    if (result.doesIntersect){
        result.point =intsecPoint;
        result.t = t;
        //std::cout<<intsecPoint<<std::endl;
       // std::cout<<t;
    }
    return result;
    
}
bool doesPointLiesInsideTriangle(mypoint3f p, Triangle T){
    mypoint3f p1 = T.getv1();
    mypoint3f p2 = T.getv2();
    mypoint3f p3 = T.getv3();
    double den = determinant(p1, p2, p3);
   // std::cout<<den<<std::endl;
    if ( den != 0){    // using cramer's rule to find roots of equation linear in x, y, z
             /* documentation at https://en.wikipedia.org/wiki/Cramer%27s_rule*/
        
      /*  std::cout<< determinant(p, p2, p3) <<std::endl;
        std::cout<< determinant(p1, p, p3)<<std::endl;
        std::cout<<  determinant(p1, p2, p)<<std::endl;
       */
        double x = determinant(p, p2, p3) / den;
        double y = determinant(p1, p, p3) /den ;
        double z = determinant(p1, p2, p) /den ;
        if (x>=0 && y>=0 && z>=0){
           // std::cout<<"a " <<x <<" "<<y<<" "<<z<<std::endl;
            return true;
        }
        else {
           // std::cout<<"else";
            return false;
        }
    }
    else return false;
    
}
mypoint3f barycentricCoordinates( mypoint3f p, Triangle T){
    mypoint3f p1 = T.getv1();
    mypoint3f p2 = T.getv2();
    mypoint3f p3 = T.getv3();
    mypoint3f result ;
    double den = determinant(p1, p2, p3);
    // std::cout<<den<<std::endl;
    if ( den != 0){    // using cramer's rule to find roots of equation linear in x, y, z
        /* documentation at https://en.wikipedia.org/wiki/Cramer%27s_rule*/
        
        /*  std::cout<< determinant(p, p2, p3) <<std::endl;
         std::cout<< determinant(p1, p, p3)<<std::endl;
         std::cout<<  determinant(p1, p2, p)<<std::endl;
         */
        double x = determinant(p, p2, p3) / den;
        double y = determinant(p1, p, p3) /den ;
        double z = determinant(p1, p2, p) /den ;
        result= mypoint3f(x,y,z);
    }
    return result;
}

bool rotateOBJ(std::vector<glm::vec3> & vertices, std::vector<glm::vec3> normals, double theta){
    double x, y,nx,ny;
    for(int i =0; i<vertices.size(); i++){
        x = vertices[i].x * cos(theta) - vertices[i].y * sin(theta) ;
        y = vertices[i].x * sin(theta) + vertices[i].y * cos(theta);
        nx = normals[i].x* cos(theta) - normals[i].y * sin(theta) ;
        ny = normals[i].x * sin(theta) + normals[i].y * cos(theta);
        vertices[i].x = x;
        vertices[i].y = y;
        normals[i].x  = nx;
        normals[i].y  = ny;
    }
    return true;
}

bool loadOBJ(
             const char * path,
             std::vector<glm::vec3> & out_vertices,
             std::vector<glm::vec3> & out_normals
             ){
    printf("Loading OBJ file %s...\n", path);
    
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    
    
    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }
    
    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            //std::cout<<"v"<<std::endl;
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
            //std::cout<<"vn"<<std::endl;
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            //std::cout<<"matches"<<matches<<std::endl;
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                fclose(file);
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
            //std::cout<<"f"<<std::endl;
        }else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
        
    }
    
    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        
        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];
        
        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        glm::vec2 uv = temp_uvs[ uvIndex-1 ];
        glm::vec3 normal = temp_normals[ normalIndex-1 ];
        
        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_normals .push_back(normal);
        
    }
    fclose(file);
    return true;
}

bool loadOBJ2(
             const char * path,
             std::vector<glm::vec3> & out_vertices,
             std::vector<glm::vec3> & out_normals
             ){
    printf("Loading OBJ file %s...\n", path);
    
    std::vector<unsigned int> vertexIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec3> temp_normals;
    
    
    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }
    
    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            //std::cout<<"v"<<std::endl;
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
          
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
            //std::cout<<"vn"<<std::endl;
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0],  &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2],  &normalIndex[2] );
           // std::cout<<"matches"<<matches<<std::endl;
            if (matches != 6){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                fclose(file);
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
            //std::cout<<"f"<<std::endl;
        }else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
        
    }
    
    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        
        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int normalIndex = normalIndices[i];
        
        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        glm::vec3 normal = temp_normals[ normalIndex-1 ];
        
        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_normals .push_back(normal);
        
    }
    fclose(file);
    return true;
}
