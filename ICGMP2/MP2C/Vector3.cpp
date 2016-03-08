//
//  Vector3.cpp
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#include "Vector3.h"

/* Basic initialization and nomalisation for Vector3 class*/

Vector3::Vector3() {
    // nothing
}

Vector3::Vector3(float a, float b, float c) {
    x = a; y = b; z = c;
}

void Vector3::normalize() {
    float m = x * x + y * y + z * z;
    if (fabsf(m) > TOLERANCE && fabsf(m - 1.0f) > TOLERANCE ) {
        float mag = sqrtf(m);
        x /= mag;
        y /= mag;
        z /= mag;
    }
}