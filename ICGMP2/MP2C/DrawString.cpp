//
//  DrawString.cpp
//  MP2C
//
//  Created by 安田圭佑 on 3/7/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#include "DrawString.h"


/* Draw strings on the window as 2d characters.
   This function use orthography to write as 2d.
   I think this function can be refactored.
 */
void DrawString::draw(string str, int w, int h, int x, int y){
    // Below functions are just like main class's init().
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //until here
    
    glRasterPos2f(x, y);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic); // write characters one by one.
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}
