//
//  Camera.h
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Quaternion.h"

class Camera {
public:
    // Elements for Camera class
    Quaternion rotation;
    Vector3 position;
    Vector3 lookAt;
    Vector3 up;
    Camera(); // Initialize
    void roll(float r); // Rotate function to roll
    void pitch(float r); // Rotate function to pitch
    void updateVectors(); // Update function for vectors
};

#endif /* Camera_h */
