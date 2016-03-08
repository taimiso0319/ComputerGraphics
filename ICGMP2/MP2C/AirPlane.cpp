//
//  AirPlane.cpp
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#include "AirPlane.h"
#include "GLUT/glut.h"

/* Initialize the move speed. */
AirPlane::AirPlane(){
    moveSpeed = 0.005f;
}

/* Update camera location lookAt vector and up vector. */
void AirPlane::updateCamera(){
    gluLookAt(cam.position.x,
              cam.position.z,
              cam.position.y,
              cam.lookAt.x + cam.position.x,
              cam.lookAt.z + cam.position.z,
              cam.lookAt.y + cam.position.y,
              cam.up.x,
              cam.up.z,
              cam.up.y);
}

/* Use Camera class to set rotate and to update vectors. */
void AirPlane::updateRoll(float deg){
    cam.roll(deg);
    cam.updateVectors();
}

/* Use Camera class to set pitch and to update vectors. */
void AirPlane::updatePitch(float deg){
    cam.pitch(deg);
    cam.updateVectors();
}

/* Move the airplane forward use lookat for directional vector to calculate translation */
void AirPlane::moveForward(){
    cam.position = cam.position + cam.lookAt * moveSpeed;
}

/* Shoot a bullet. the number of bullets depened Bullet class's defined MAX_BULLET */
void AirPlane::shootBullet(){
    for(int i = 0; i < MAX_BULLET; i++){
        if(!bul[i].shooted){
            bul[i] = Bullet(cam.position); // Set the initialize location of the bullet
            bul[i].setForward(cam.lookAt); // Set the foward vector of the bullet
            bul[i].setShooted(true); // Set a bool the bullet shooted or not.
        }
    }
}

/* Draw the bullet sphere. 
   This function only works when the bullet has/have already shooted. */
void AirPlane::drawBullet(){
    for(int i = 0; i < MAX_BULLET; i++){
        if(bul[i].shooted){
            bul[i].moveForward();
            bul[i].drawBullet();
        }
    }
}