//
//  Bullet.cpp
//  MP2C
//
//  Created by 安田圭佑 on 3/8/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#include "Bullet.h"
#include "GLUT/glut.h"

/* Basic initialization. */
Bullet::Bullet(){
    cood = Vector3(0,0,0);
    forward = Vector3(1,0,0);
    moveSpeed = 0.1f;
    counter = 0;
}

/* Initialize with Vector3 */
Bullet::Bullet(Vector3 vec){
    cood = vec;
    forward = Vector3(1,0,0);
    moveSpeed = 0.1f;
    counter = 0;
}

/* Set bullet forward */
void Bullet::setForward(Vector3 vec){
    forward = vec;
}

/* Move bullet forward 
   Just liek move aireplane forward */
void Bullet::moveForward(){
    cood = cood + forward * moveSpeed;
}

/* Draw bullet in the world.
   If the bullet(s) moves enough stop to draw the bullet.
   And then it will be able to shoot again.*/
void Bullet::drawBullet(){
    if(counter < 50){
        glTranslatef(cood.x, cood.z, cood.y);
        glutSolidSphere(0.05f, 32, 16);
        counter++;
    }else{
        shooted = !shooted;
    }
}
/* Just set bool the bullet shooted or not
   if the shooted is false, it means you cannot shoot the bullets anymore*/
void Bullet::setShooted(bool b){
    shooted = b;
}