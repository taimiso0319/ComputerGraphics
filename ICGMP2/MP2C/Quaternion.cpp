//
//  Quaternion.cpp
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

// This class referenced http://content.gpwiki.org/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation#Rotating_vectors
// and http://www.cprogramming.com/tutorial/3d/quaternions.html
// but something was wrong for this project so I edited it.

#include "Quaternion.h"

/* Basic initialization and nomalisation for Quaternion class*/

Quaternion::Quaternion(float a, float b, float c, float d) {
    w = a; x = b; y = c; z = d;
}
Quaternion::Quaternion() {

}

/* normalising a quaternion works similar to a vector. This method will not do anything
   if the quaternion is close enough to being unit-length. define TOLERANCE as something
   small like 0.00001f to get accurate results */
void Quaternion::normalise() {
    float m = x * x + y * y + z * z + w * w;
    if (fabsf(m) > TOLERANCE && fabsf(m - 1.0f) > TOLERANCE ) {
        float mag = sqrtf(m);
        w /= mag;
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

/* I need to get the inverse of a quaternion to properly apply a quaternion-rotation to a vector
   The conjugate of a quaternion is the same as the inverse, as long as the quaternion is unit-length */
Quaternion Quaternion::getConjugate() const {
    return Quaternion(w,-x,-y,-z);
}

// Get rotation quaternion convert from Euler Angles
// ... but its useless so I didn't use it to control airplane.
void Quaternion::FromEuler(float pitch, float yaw, float roll) {
    
    float p = pitch * PIOVER180 / 2.0f;
    float y = yaw * PIOVER180 / 2.0f;
    float r = roll * PIOVER180 / 2.0f;
    
    float sinp = sin(p);
    float siny = sin(y);
    float sinr = sin(r);
    float cosp = cos(p);
    float cosy = cos(y);
    float cosr = cos(r);
    
    this->x = sinr * cosp * cosy - cosr * sinp * siny;
    this->y = cosr * sinp * cosy + sinr * cosp * siny;
    this->z = cosr * cosp * siny - sinr * sinp * cosy;
    this->w = cosr * cosp * cosy + sinr * sinp * siny;
    
    normalise();
}