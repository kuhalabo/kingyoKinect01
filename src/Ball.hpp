//
//  Ball.hpp
//  kingyoKinect01
//
//  Created by kuha on 2016/09/30.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>

#endif /* Ball_hpp */

#pragma once
#include "ofMain.h"

class Ball {
public:
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    float radius;
    ofColor bcolor;
    int fish;
    bool visible;
    
public:
    Ball();
    ~Ball();
    void draw();
    void update();
    
};
