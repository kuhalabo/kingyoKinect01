//
//  kinectShadowHand.hpp
//  kingyoKinect01
//
//  Created by kuha on 2016/09/30.
//
//

#ifndef kinectShadowHand_hpp
#define kinectShadowHand_hpp

#include <stdio.h>

#endif /* kinectShadowHand_hpp */

#pragma once

#include "ofMain.h"

// kinect setting
#include "ofxOpenCv.h"
#include "ofxKinect.h"


class kinectShadowHand : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void exit(); // kinect exit
    
    void keyPressed(int key);
    
    //--------------------------
    // kinect setting
    //    void windowResized(int w, int h);
    //    ofxKinect kinect; //Kinect instance
    ofxKinect kinect;
    ofImage kinectImage; // Kinect camera image
    ofImage depthImage; // Kinect depth image
    ofImage threshImage;
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage01; // grayscale depth image
    ofxCvGrayscaleImage grayImage02; // grayscale depth image
    //ofxCvGrayscaleImage grayImage03; // grayscale depth image
    
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvContourFinder contourFinder01;
    ofxCvContourFinder contourFinder02;
    //ofxCvContourFinder contourFinder03;
    
    //--------------------------

    int rows, cols;
    //bool active;
    
    bool bThreshWithOpenCV;
    
    int nearThreshold01,nearThreshold02,nearThreshold03;
    int farThreshold01,farThreshold02,farThreshold03;
    int angle = 15;
    
    int depth_min = 120; //影を検出するデプス値の最も大きい（近い）値
    //int depth_min = 150;
    int depth_dif = 40;//２つの影のレイヤーのテプス値の差
    int alphaGray = 50; // 人影のアルファ値
    int alphaSpring = 100;// 重心に描画する図形の陰のアルファ値
    int getInfo = -1;
    //int cellDirection = 0;
//#define NCENTROID 3
    int nCentroid = 3; // セル生成場所の重心の検出個数
    ofVec2f posCentroid[10];
    ofColor shadwColor01 = ofColor::magenta;
    ofColor shadwColor02 = ofColor::blue;
    
    

    //--------------------------
   
};
