//
//  triangle.hpp
//  hw3class
//
//  Created by ललित सिंह on 28/10/2016.
//  Copyright © 2016 ललित सिंह. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include "mypoint3f.hpp"
class Triangle{
private:
    mypoint3f v1;
    mypoint3f v2;
    mypoint3f v3;
public:
    Triangle();
    Triangle(mypoint3f, mypoint3f, mypoint3f);
    mypoint3f getv1();
    mypoint3f getv2();
    mypoint3f getv3();
    friend std::ostream& operator <<(std::ostream&, Triangle&);
    
    
};
#endif /* triangle_hpp */
