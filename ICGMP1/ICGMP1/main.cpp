#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
using namespace std;

#define PI 3.1415926

#define ANGLE 0.1

char TitleString[ ] = "OpenGL";
float randXCo[12];
float randYCo[12];
float randXCo2[12];
float randYCo2[12];
float finalXCo[12] = {
    -1.3, -1.3, -0.9, -0.9, -1.3, -1.3, -0.1, -0.1, -0.5, -0.5, -0.1, -0.1
};

float finalYCo[12] = {
    1.0, 0.6, 0.6, -0.6, -0.6, -1.0, -1.0, -0.6, -0.6, 0.6, 0.6, 1.0
};

float finalXCo2[12] = {
    0.1, 0.1, 0.5, 0.5, 0.1, 1.3, 0.7, 1.3
};

float finalYCo2[12] = {
    1.0, 0.4, 1.0, -0.6, -1.0, -1.0, -1.0, -0.6
};

float finalZCo[12];
float finalZCo2[12];

float XCo[12];
float YCo[12];
float ZCo[12];
float XCo2[12];
float YCo2[12];
float ZCo2[12];

float randomRange = 0;

bool randFlag = false;
bool loop = false;

GLfloat Camera[]{0, 0, 20, 0};

GLfloat translate[] = {
    1 , 0 , 0 , 0 ,
    0 , 1 , 0 , 0 ,
    0 , 0 , 1 , 0 ,
    0 , 0 , 0 , 1
};
GLfloat unit[] = {
    1 , 0 , 0 , 0 ,
    0 , 1 , 0 , 0 ,
    0 , 0 , 1 , 0 ,
    0 , 0 , 0 , 1
};


void myInit(){
    glLoadIdentity();
    gluLookAt(Camera[0], Camera[1], Camera[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    for(int i = 0; i < sizeof(XCo) / sizeof(XCo[0]); i++){
        XCo[i] = 0;
        YCo[i] = 0;
        ZCo[i] = 0;
        XCo2[i] = 0;
        YCo2[i] = 0;
        ZCo2[i] = 0;
    }
}

double GetRandom(double min, double max){
    return min + (double)(rand() * (max-min)/RAND_MAX);
}

void ShapeTransform(int value){
    if(value > 120){
        for(int i = 0; i < sizeof(randXCo) / sizeof(randXCo[0]); i++){
            randXCo[i] = GetRandom(-randomRange, randomRange);
            randXCo2[i] = GetRandom(-randomRange, randomRange);
        }
        for(int i = 0; i < sizeof(randYCo) / sizeof(randYCo[0]); i++){
            randYCo[i] = GetRandom(-randomRange, randomRange);
            randYCo2[i] = GetRandom(-randomRange, randomRange);
        }
    }if(value > 240){
        for(int i = 0; i < sizeof(XCo) / sizeof(XCo[0]); i++){
            XCo[i] -= finalXCo[i] / 150;
            YCo[i] -= finalYCo[i] / 150;
            XCo2[i] -= finalXCo2[i] / 150;
            YCo2[i] -= finalYCo2[i] / 150;
        }
        randomRange -= 0.001;
        if(XCo[0] > 0){
            for(int i = 0; i < sizeof(XCo) / sizeof(XCo[0]); i++){
                XCo[i] = 0;
                YCo[i] = 0;
                XCo2[i] = 0;
                YCo2[i] = 0;
            }
            randomRange = 0;
            loop = true;
            myInit();
            glutTimerFunc(33, IncreaseScale, 0);
            return;
        }
    }
    translate[0] = cos(ANGLE);
    translate[2] = -sin(ANGLE);
    translate[8] = sin(ANGLE);
    translate[10] = cos(ANGLE);
    glMultMatrixf(translate);
    glutPostRedisplay();
    glutTimerFunc(33 , ShapeTransform , value + 1);
}

void IncreaseScale(int value){
    if(loop){
        for(int i = 0; i < sizeof(XCo) / sizeof(XCo[0]); i++){
            XCo[i] += finalXCo[i] / 150;
            YCo[i] += finalYCo[i] / 150;
            XCo2[i] += finalXCo2[i] / 150;
            YCo2[i] += finalYCo2[i] / 150;
        }
        randomRange += 0.001;
        if(XCo[0] < finalXCo[0]){
            for(int i = 0; i < sizeof(XCo) / sizeof(XCo[0]); i++){
                XCo[i] = finalXCo[i];
                YCo[i] = finalYCo[i];
                XCo2[i] = finalXCo2[i];
                YCo2[i] = finalYCo2[i];
            }
            loop = false;
            randomRange = 0.15;
            glutTimerFunc(33, ShapeTransform, 0);
        }
        glutPostRedisplay();
        if(loop)glutTimerFunc(33, IncreaseScale, 0);
    }
}


static void key(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
    }
}

void shape(){
    
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 0.6, 0);
    glVertex3d(XCo[1] + randXCo[1] , YCo[1] + randYCo[1],  ZCo[1]);  //2
    glColor3f(1, 0.4, 0);
    glVertex3d(XCo[0] + randXCo[0] , YCo[0] + randYCo[0],  ZCo[0]);  //1
    glColor3f(1, 0.6, 0);
    glVertex3d(XCo[2] + randXCo[2] , YCo[2] + randYCo[2],  ZCo[2]);  //3
    glColor3f(1, 0.4, 0);
    glVertex3d(XCo[0] + randXCo[0] , YCo[0] + randYCo[0],  ZCo[0]);  //1
    glColor3f(1, 0.6, 0);
    glVertex3d(XCo[11]+ randXCo[11], YCo[11]+ randYCo[11], ZCo[11]); //12
    glVertex3d(XCo[11]+ randXCo[11], YCo[11]+ randYCo[11], ZCo[11]); //12
    glVertex3d(XCo[10]+ randXCo[10], YCo[10]+ randYCo[10], ZCo[10]); //11
    glVertex3d(XCo[9] + randXCo[9] , YCo[9] + randYCo[9],  ZCo[9]);  //10
    glVertex3d(XCo[11]+ randXCo[11], YCo[11]+ randYCo[11], ZCo[11]); //12
    glVertex3d(XCo[2] + randXCo[2] , YCo[2] + randYCo[2],  ZCo[2]);  //3
    glVertex3d(XCo[9] + randXCo[9] , YCo[9] + randYCo[9],  ZCo[9]);  //10
    glVertex3d(XCo[3] + randXCo[3] , YCo[3] + randYCo[3],  ZCo[3]);  //4
    glVertex3d(XCo[8] + randXCo[8] , YCo[8] + randYCo[8],  ZCo[8]);  //9
    glVertex3d(XCo[3] + randXCo[3] , YCo[3] + randYCo[3],  ZCo[3]);  //4
    glVertex3d(XCo[4] + randXCo[4] , YCo[4] + randYCo[4],  ZCo[4]);  //5
    glVertex3d(XCo[3] + randXCo[3] , YCo[3] + randYCo[3],  ZCo[3]);  //4
    glVertex3d(XCo[5] + randXCo[5] , YCo[5] + randYCo[5],  ZCo[5]);  //6
    glVertex3d(XCo[8] + randXCo[8] , YCo[8] + randYCo[8],  ZCo[8]);  //9
    glColor3f(1, 0.4, 0);
    glVertex3d(XCo[6] + randXCo[6] , YCo[6] + randYCo[6],  ZCo[6]);  //7
    glColor3f(1, 0.6, 0);
    glVertex3d(XCo[7] + randXCo[7] , YCo[7] + randYCo[7],  ZCo[7]);  //8
    glEnd();
}

void shape2() {
    //glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.1, 0.1, 1.0);
    glVertex3d(XCo2[0] + randXCo2[0], YCo2[0] + randYCo2[0], ZCo2[0]); //1
    glColor3f(0.2, 0.2, 1.0);
    glVertex3d(XCo2[2] + randXCo2[2], YCo2[2] + randYCo2[2], ZCo2[2]); //3
    glColor3f(0.35, 0.35, 1.0);
    glVertex3d(XCo2[1] + randXCo2[1], YCo2[1] + randYCo2[1], ZCo2[1]); //2
    glVertex3d(XCo2[3] + randXCo2[3], YCo2[3] + randYCo2[3], ZCo2[3]); //4
    glVertex3d(XCo2[4] + randXCo2[4], YCo2[4] + randYCo2[4], ZCo2[4]); //5
    glVertex3d(XCo2[6] + randXCo2[6], YCo2[6] + randYCo2[6], ZCo2[6]); //7
    glVertex3d(XCo2[3] + randXCo2[3], YCo2[3] + randYCo2[3], ZCo2[3]); //4
    glVertex3d(XCo2[7] + randXCo2[7], YCo2[7] + randYCo2[7], ZCo2[7]); //8
    glVertex3d(XCo2[6] + randXCo2[6], YCo2[6] + randYCo2[6], ZCo2[6]); //7
    glColor3f(0.2, 0.2, 1.0);
    glVertex3d(XCo2[5] + randXCo2[5], YCo2[5] + randYCo2[5], ZCo2[5]); //6
    glEnd();
}

void disp(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shape();
    shape2();
    glFlush();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(10.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc , char ** argv){
    glutInit(&argc , argv);
    glutInitWindowPosition(500 , 200);
    glutInitWindowSize(600 , 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow(TitleString);
    myInit();
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);
    glutDisplayFunc(disp);
    loop = true;
    glutTimerFunc(33, IncreaseScale, 0);
    glutMainLoop();
    return 0;
}