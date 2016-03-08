//
//  Bullet.h
//  MP2C
//
//  Created by 安田圭佑 on 3/8/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

#include "Quaternion.h"

class Bullet{
public:
    // Basic elements and functions.
    int counter;
    bool shooted;
    Vector3 cood;
    Vector3 forward;
    float moveSpeed;
    Bullet(); //Init
    Bullet(Vector3 vec);
    void moveForward();
    void setForward(Vector3 vec);
    void drawBullet();
    void setShooted(bool b);
};

#endif /* Bullet_h */
