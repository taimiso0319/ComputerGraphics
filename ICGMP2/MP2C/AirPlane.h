//
//  AirPlane.h
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#ifndef AirPlane_h
#define AirPlane_h

#define MAX_BULLET 1

#include "Camera.h"
#include "Bullet.h"

class AirPlane{
public:
    Camera cam;
    float moveSpeed; // Speed of airplane. I didn't make speed controller this time.
    Bullet bul[MAX_BULLET]; // To shoot the bullet.
    AirPlane(); // Init
    void updateCamera();
    void updateRoll(float deg);
    void updatePitch(float deg);
    void moveForward();
    void shootBullet();
    void drawBullet();
};

#endif /* AirPlane_h */
