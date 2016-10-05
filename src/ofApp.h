#pragma once

#include "ofMain.h"
#include "ofGraphics.h"

#include "kinectShadowHand.hpp"
#include "Bird.hpp"
#include "Ball.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
// kinectShadowHand
    kinectShadowHand shadowHand;
    
// Boids
    bool mouse_pressed;
    ofVec2f mousePos;

    vector<Bird> birds1;
    vector<Bird> birds2;
    vector<Bird> birds3;
    vector<Bird> birds4;
    vector<Bird> nullBirds;
    
    void ballGenerate(ofVec2f _pos, float _radius);
    void setColorDayNight();
    void setNightMode(int h);
    
    //    Ball myball;
    vector<Ball> balls;
    
    ofColor bgcolor;
    ofColor color1;
    ofColor color2;
    ofColor color3;
    ofColor color4;
    ofColor color5;

    int ballsNum;
    int counterBall;
    
    // sound
/*
    void audioIn(float * input, int bufferSize, int nChannels);
    ofSoundStream soundStream;
    float curVol;
*/    
};
