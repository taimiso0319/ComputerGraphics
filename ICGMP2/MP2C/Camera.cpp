//
//  Camera.cpp
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

/* Some of this class functions referenced http://content.gpwiki.org/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation#Rotating_vectors
   and http://www.cprogramming.com/tutorial/3d/quaternions.html */

#include "Camera.h"
/* Initialize a Camera class */
Camera::Camera() {
    position = Vector3(0,0.05,0);
    rotation = Quaternion(1.0,0.0,0.0,0.0);
    lookAt = Vector3(1,0,0);
    up = Vector3(0,1,0);
    rotation.normalise();
}

/* Rotate as "Up" axis */
void Camera::roll(float r) {
    Vector3 v = rotation * Vector3(1.0,0.0,0.0);
    Quaternion nrot(r,v.x,v.y,v.z);
    nrot.normalise();
    rotation = nrot * rotation;
    rotation.normalise();
}
/* Rotate as "R" axis */
void Camera::pitch(float r) {
    Vector3 v = rotation * Vector3(0.0,0.0,1.0);
    Quaternion nrot(r,v.x,v.y,v.z);
    nrot.normalise();
    rotation = nrot * rotation;
    rotation.normalise();
}

/* Calculate and update lookAt and up vectors. */
void Camera::updateVectors() {
    Vector3 v = rotation * Vector3(1.0,0.0,0.0);
    lookAt.x = v.x;
    lookAt.y = v.y;
    lookAt.z = v.z;
    
    v = rotation * Vector3(0.0,1.0,0.0);
    up.x = v.x;
    up.y = v.y;
    up.z = v.z;
}