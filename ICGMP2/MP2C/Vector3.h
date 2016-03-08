//
//  Vector3.h
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#ifndef Vector3_h
#define Vector3_h

// these defined variable are used by Quaternion and Airplane control.


#define DEGREE 60
#define TOLERANCE  0.00001f
// I think I didn't need below valiables.
#define PI 3.14159
#define PIOVER180 PI/180

#include <stdio.h>
#include <math.h>
class Vector3 {
public:
    float x, y, z; //vector3 elements
    
    Vector3();
    Vector3(float a, float b, float c);
    
    // Basice operators to calculate four calculus.
    Vector3 operator+( const Vector3 v) const{
        return Vector3(x+v.x,y+v.y,z+v.z);
    };
    Vector3 operator-( const Vector3 v) const{
        return Vector3(x-v.x,y-v.y,z-v.z);
    };
    Vector3 operator*( const float f) const{
        return Vector3(x*f,y*f,z*f);
    };
    Vector3 operator/( const float f) const{
        return Vector3(x/f,y/f,z/f);
    };
    
    void normalize();
};


#endif /* Vector3_h */
