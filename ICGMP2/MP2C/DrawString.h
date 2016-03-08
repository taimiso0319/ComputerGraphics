//
//  DrawString.h
//  MP2C
//
//  Created by 安田圭佑 on 3/7/16.
//  Copyright © 2016 安田圭佑. All rights reserved.
//

#ifndef DrawString_h
#define DrawString_h

#include <stdio.h>
#include <string>
#include "GLUT/glut.h"

using namespace std;

class DrawString{
public:
    void draw(string str, int w, int h, int x, int y); // Only this! Should I make this class?
};
#endif /* DrawString_h */
