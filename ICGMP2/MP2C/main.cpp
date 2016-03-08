//
//  main.cpp
//  MP2C
//
//  Created by 安田圭佑 on 3/4/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "AirPlane.h"
#include "DrawString.h"

float sealevel;

int res = 1025;

#define ADDR(i,j,k) (3*((j)*res + (i)) + (k))

GLfloat *verts = 0;
GLfloat *norms = 0;
GLuint *faces = 0;

/* The classes that I made. 
 The AirPlane class to control an aiplane(Camera).
 The DrawString class to draw strings to show help.
 */
AirPlane ap;
DrawString ds;

// Key down flags.
bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool showHelp = true;

/* Its not my code from here */
float frand(float x, float y) {
    static int a = 1688135690, b = 111769901; // I changed seed a little
    int xi = *(int *)&x;
    int yi = *(int *)&y;
    srand(((xi * a) % b) - ((yi * b) % a));
    return 2.0*((float)rand()/(float)RAND_MAX) - 1.0;
}
void mountain(int i, int j, int s)
{
    if (s > 1) {
        
        float x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3,x01,y01,z01,x02,y02,z02,x13,y13,z13,x23,y23,z23,x0123,y0123,z0123;
        
        x0 = verts[ADDR(i,j,0)];
        y0 = verts[ADDR(i,j,1)];
        z0 = verts[ADDR(i,j,2)];
        
        x1 = verts[ADDR(i+s,j,0)];
        y1 = verts[ADDR(i+s,j,1)];
        z1 = verts[ADDR(i+s,j,2)];
        
        x2 = verts[ADDR(i,j+s,0)];
        y2 = verts[ADDR(i,j+s,1)];
        z2 = verts[ADDR(i,j+s,2)];
        
        x3 = verts[ADDR(i+s,j+s,0)];
        y3 = verts[ADDR(i+s,j+s,1)];
        z3 = verts[ADDR(i+s,j+s,2)];
        
        x01 = 0.5*(x0 + x1);
        y01 = 0.5*(y0 + y1);
        z01 = 0.5*(z0 + z1);
        
        x02 = 0.5*(x0 + x2);
        y02 = 0.5*(y0 + y2);
        z02 = 0.5*(z0 + z2);
        
        x13 = 0.5*(x1 + x3);
        y13 = 0.5*(y1 + y3);
        z13 = 0.5*(z1 + z3);
        
        x23 = 0.5*(x2 + x3);
        y23 = 0.5*(y2 + y3);
        z23 = 0.5*(z2 + z3);
        
        x0123 = 0.25*(x0 + x1 + x2 + x3);
        y0123 = 0.25*(y0 + y1 + y2 + y3);
        z0123 = 0.25*(z0 + z1 + z2 + z3);
        
        z01 += 0.5*((float)s/res)*frand(x01,y01);
        z02 += 0.5*((float)s/res)*frand(x02,y02);
        z13 += 0.5*((float)s/res)*frand(x13,y13);
        z23 += 0.5*((float)s/res)*frand(x23,y23);
        z0123 += 0.5*((float)s/res)*frand(x0123,y0123);
        
        verts[ADDR(i+s/2,j,0)] = x01;
        verts[ADDR(i+s/2,j,1)] = y01;
        verts[ADDR(i+s/2,j,2)] = z01;
        
        verts[ADDR(i,j+s/2,0)] = x02;
        verts[ADDR(i,j+s/2,1)] = y02;
        verts[ADDR(i,j+s/2,2)] = z02;
        
        verts[ADDR(i+s,j+s/2,0)] = x13;
        verts[ADDR(i+s,j+s/2,1)] = y13;
        verts[ADDR(i+s,j+s/2,2)] = z13;
        
        verts[ADDR(i+s/2,j+s,0)] = x23;
        verts[ADDR(i+s/2,j+s,1)] = y23;
        verts[ADDR(i+s/2,j+s,2)] = z23;
        
        verts[ADDR(i+s/2,j+s/2,0)] = x0123;
        verts[ADDR(i+s/2,j+s/2,1)] = y0123;
        verts[ADDR(i+s/2,j+s/2,2)] = z0123;
        
        mountain(i,j,s/2);
        mountain(i+s/2,j,s/2);
        mountain(i,j+s/2,s/2);
        mountain(i+s/2,j+s/2,s/2);
        
    } else {
        
        float dx,dy,dz;
        
        if (i == 0) {
            dx = verts[ADDR(i+1,j,2)] - verts[ADDR(i,j,2)];
        } else if (i == res-1) {
            dx = verts[ADDR(i,j,2)] - verts[ADDR(i-1,j,2)];
        } else {
            dx = (verts[ADDR(i+1,j,2)] - verts[ADDR(i-1,j,2)])/2.0;
        }
        
        if (j == 0) {
            dy = verts[ADDR(i,j+1,2)] - verts[ADDR(i,j,2)];
        } else if (j == res-1) {
            dy = verts[ADDR(i,j,2)] - verts[ADDR(i,j-1,2)];
        } else {
            dy = (verts[ADDR(i,j+1,2)] - verts[ADDR(i,j-1,2)])/2.0;
        }
        
        dx *= res;
        dy *= res;
        dz = 1.0/sqrt(dx*dx + dy*dy + 1.0);
        dx *= dz;
        dy *= dz;
        
        norms[ADDR(i,j,0)] = dx;
        norms[ADDR(i,j,1)] = dy;
        norms[ADDR(i,j,2)] = dz;
    }
}

void makemountain()
{
    int i,j;
    
    if (verts) free(verts);
    if (norms) free(norms);
    if (faces) free(faces);
    
    verts = (GLfloat *)malloc(res*res*3*sizeof(GLfloat));
    norms = (GLfloat *)malloc(res*res*3*sizeof(GLfloat));
    faces = (GLuint *)malloc((res-1)*(res-1)*6*sizeof(GLuint));
    
    verts[ADDR(0,0,0)] = -5.0;
    verts[ADDR(0,0,1)] = -5.0;
    verts[ADDR(0,0,2)] = 0.0;
    
    verts[ADDR(res-1,0,0)] = 5.0;
    verts[ADDR(res-1,0,1)] = -5.0;
    verts[ADDR(res-1,0,2)] = 0.0;
    
    verts[ADDR(0,res-1,0)] = -5.0;
    verts[ADDR(0,res-1,1)] = 5.0;
    verts[ADDR(0,res-1,2)] = 0.0;
    
    verts[ADDR(res-1,res-1,0)] = 5.0;
    verts[ADDR(res-1,res-1,1)] = 5.0;
    verts[ADDR(res-1,res-1,2)] = 0.0;
    
    mountain(0,0,res-1);
    
    GLuint *f = faces;
    for (j = 0; j < res-1; j++) {
        for (i = 0; i < res-1; i++) {
            *f++ = j*res + i;
            *f++ = j*res + i + 1;
            *f++ = (j+1)*res + i + 1;
            *f++ = j*res + i;
            *f++ = (j+1)*res + i + 1;
            *f++ = (j+1)*res + i;
        }
    }
    
}

void init(void) 
{
    GLfloat amb[] = {0.2,0.2,0.2};
    GLfloat diff[] = {1.0,1.0,1.0};
    GLfloat spec[] = {1.0,1.0,1.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    
    glClearColor (0.5, 0.5, 1.0, 0.0);	// sky
    glEnable(GL_DEPTH_TEST);
    
    sealevel = -0.2;
    
    makemountain();
}
/* to here */

/* The drawStrigns function to write help using the DrawString class.
   This is actually how to control. */
void drawStrings(){
    glColor3d(0.2, 0.2, 0.2);
    ds.draw("  h   key to show/hide help",  GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 5);
    if(showHelp){
        ds.draw("  UP  key to pitch down",      GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 10);
        ds.draw(" Down key to pitch up",        GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 14);
        ds.draw(" Left key to roll left",       GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 18);
        ds.draw("Right key to roll right",      GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 22);
        ds.draw("  +   key to sealevel up",     GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 26);
        ds.draw("  -   key to sealevel down",   GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 30);
        ds.draw("  f   key to resolution up",   GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 34);
        ds.draw("  c   key to resolution down", GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 38);
        ds.draw("Space key to shoot a bullet",  GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 1, 42);
    }
}

/* The keyboardFlag function for glutSpecialFunc and glutSpecialUpFunc
   Airplane rotates/pitches smoothly when the bool flags are true. */
void keyboardFlag(){
    if(leftKey){
        ap.updateRoll(DEGREE);
    }
    if(rightKey){
        ap.updateRoll(-DEGREE);
    }
    if(upKey){
        ap.updatePitch(-DEGREE);
    }
    if(downKey){
        ap.updatePitch(DEGREE);
    }
}
/* This function is based on the mountain-retained.cpp 
   but I changed some lines to use functions I made */
void display(void)
{
    GLfloat tanamb[] = {0.2,0.15,0.1,1.0};
    GLfloat tandiff[] = {0.4,0.3,0.2,1.0};
    GLfloat tanspec[] = {0.0,0.0,0.0,1.0};	// dirt doesn't glisten
    
    GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
    GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
    GLfloat seaspec[] = {0.5,0.5,1.0,1.0};	// Single polygon, will only have highlight if light hits a vertex just right
    
    GLfloat lpos[] = {0.0,0.0,10.0,0.0};	// sun, high noon
    
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLoadIdentity ();             /* clear the matrix */

    keyboardFlag();    // Check keyboard flag to control.
    ap.moveForward();  // Move forward automatically.
    ap.updateCamera(); // Update lookat camera.
    drawStrings();     // Draw strings on window.
    
    // send the light position down as if it was a vertex in world coordinates
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    
    // load terrain material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tanspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
    
    // Send terrain mesh through pipeline
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,verts);
    glNormalPointer(GL_FLOAT,0,norms);
    glDrawElements(GL_TRIANGLES, 6*(res-1)*(res-1), GL_UNSIGNED_INT, faces);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    // load water material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
    // Send water as a single quad
    glNormal3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex3f(-5,-5,sealevel);
    glVertex3f(5,-5,sealevel);
    glVertex3f(5,5,sealevel);
    glVertex3f(-5,5,sealevel);
    glEnd();
    
    ap.drawBullet(); // Draw bullet.
    
    glutSwapBuffers();
    glFlush ();
    
    glutPostRedisplay();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0,(float)w/h,0.01,10.0);
    glMatrixMode (GL_MODELVIEW);
}
/* Below two functions manage only flag. 
   Behavior depends keyboardFlag() */
void arrowkeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            leftKey = true;
            break;
        case GLUT_KEY_RIGHT:
            rightKey = true;
            break;
        case GLUT_KEY_UP:
            upKey = true;
            break;
        case GLUT_KEY_DOWN:
            downKey = true;
            break;
    }
}

void allowkeysup(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
            leftKey = false;
            break;
        case GLUT_KEY_RIGHT:
            rightKey = false;
            break;
        case GLUT_KEY_UP:
            upKey = false;
            break;
        case GLUT_KEY_DOWN:
            downKey = false;
            break;
    }
}
/* I added 'h' key and space bar. */
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case '-':
            sealevel -= 0.01;
            break;
        case '+':
        case '=':
            sealevel += 0.01;
            break;
        case 'f':
            res = (res-1)*2 + 1;
            makemountain();
            break;
        case 'c':
            res = (res-1)/2 + 1;
            makemountain();
            break;
        case 'h':
            showHelp = !showHelp; // Show/Hide help.
            break;
        case ' ':
            ap.shootBullet(); // Make bullet into the world and initialize it.
            break;
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowkeys);     // These two lines for control airplane smoothly.
    glutSpecialUpFunc(allowkeysup); // These functions manage flags.
    glutMainLoop();
    return 0;
}
