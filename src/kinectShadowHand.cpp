//
//  kinectShadowHand.cpp
//  kingyoKinect01
//
//  Created by kuha on 2016/09/30.
//
//

#include "kinectShadowHand.hpp"

void kinectShadowHand::setup() {
    //    kinectSetup();
    kinect.setRegistration(true);
    
    kinect.init();
    kinect.open();		// opens first available kinect
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage01.allocate(kinect.width, kinect.height);
    grayImage02.allocate(kinect.width, kinect.height);
//    grayImage03.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    farThreshold03 = depth_min;
    nearThreshold03 = farThreshold03 + depth_dif;
    farThreshold02 = nearThreshold03;
    nearThreshold02 = farThreshold02 + depth_dif;
    farThreshold01 = nearThreshold02;
    nearThreshold01 = farThreshold01 + depth_dif;
    
    bThreshWithOpenCV = true;
    
    // zero the tilt on startup
    kinect.setCameraTiltAngle(angle);
    
   
}

void kinectShadowHand::update() {
    //---------------------------
    // kinect
    //    kinectUpdate();
    kinect.update();
    if(kinect.isFrameNew()) {

// 01 layer
        grayImage01.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage01;
            grayThreshFar = grayImage01;
            grayThreshNear.threshold(nearThreshold01, true);
            grayThreshFar.threshold(farThreshold01);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage01.getCvImage(), NULL);
        } else {
/*
            // or we do it ourselves - show people how they can work with the pixels
            unsigned char * pix = grayImage01.getPixels();
            
            int numPixels = grayImage01.getWidth() * grayImage01.getHeight();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold01 && pix[i] > farThreshold01) {
                    pix[i] = 255;
                    //pix[i] = 25;
                } else {
                    pix[i] = 0;
                    //pix[i] = 23;
                }
            }
 */
        }
        // update the cv images
        grayImage01.flagImageChanged();
        contourFinder01.findContours(grayImage01, 50, (kinect.width*kinect.height)/4, nCentroid, false);
        
// 02 layer
        // load grayscale depth image from the kinect source
        grayImage02.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage02;
            grayThreshFar = grayImage02;
            grayThreshNear.threshold(nearThreshold02, true);
            grayThreshFar.threshold(farThreshold02);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage02.getCvImage(), NULL);
        } else {
/*
            // or we do it ourselves - show people how they can work with the pixels
            unsigned char * pix = grayImage02.getPixels();
            
            int numPixels = grayImage02.getWidth() * grayImage02.getHeight();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold02 && pix[i] > farThreshold02) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
 */
        }
        grayImage02.flagImageChanged();
        contourFinder02.findContours(grayImage02, 50, (kinect.width*kinect.height)/4, nCentroid, false);
 
        /*
        grayImage03.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage03;
            grayThreshFar = grayImage03;
            grayThreshNear.threshold(nearThreshold03, true);
            grayThreshFar.threshold(farThreshold03);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage03.getCvImage(), NULL);
        } else {
            // or we do it ourselves - show people how they can work with the pixels
            unsigned char * pix = grayImage03.getPixels();
            
            int numPixels = grayImage03.getWidth() * grayImage03.getHeight();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold03 && pix[i] > farThreshold03) {
                    pix[i] = 255;
                    //pix[i] = 25;
                } else {
                    pix[i] = 0;
                    //pix[i] = 23;
                }
            }
        }
        
        // update the cv images
        grayImage03.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder03.findContours(grayImage03, 10, (kinect.width*kinect.height)/2, 20, false);
        */
    }
    
}

void kinectShadowHand::draw() {
    const int TICK_INTERVAL = 3;
   ofSetRectMode(OF_RECTMODE_CORNER);
    ofScale(-1, 1);
    ofTranslate(ofGetWidth() * (-1), 0);
    //------------------------------------
    // kinect
    // draw from the live kinect
    //        ofSetColor(86, 119, 252, 20);
    //        grayImage03.draw(0, 0, wfull, hfull);

    ofSetColor(shadwColor02, 10);
    grayImage02.draw(0, 0, ofGetWidth(), ofGetHeight());
//    grayImage02.draw(0, 0, kinect.width + 50, kinect.height);
    
    
    ofSetColor(shadwColor01, 10);
    grayImage01.draw(0, 0, ofGetWidth(), ofGetHeight());
//    grayImage01.draw(0, 0, kinect.width + 50, kinect.height);
    
    int centroX01;
    int centroY01;
//    ofScale(ofGetWidth()/(float)kinect.width, ofGetHeight()/(float)kinect.height);

    int maxNCentro = contourFinder01.blobs.size();
    for( int i = 0; i < nCentroid; i++){
        posCentroid[i].set(0, 0);
        if( i < maxNCentro){
            centroX01 = contourFinder01.blobs[i].centroid.x * ofGetWidth()/(float)kinect.width;
            centroY01 = contourFinder01.blobs[i].centroid.y * ofGetHeight()/(float)kinect.height;
            if(centroX01 > 0 && centroX01 < ofGetWidth() && centroY01 > 0 && centroY01 < ofGetHeight()){
//                ofSetColor(ofColor::white, alphaSpring);
                posCentroid[i].set(centroX01,centroY01);
                ofSetColor(ofColor::white, 80);
                ofDrawCircle(posCentroid[i], 25); // Centroid draw
            }
        }
    }
    
    if( getInfo > 0 ){
        stringstream reportScreen;
        reportScreen << "wfull=" << ofGetWidth() << ",hfull=" << ofGetHeight() << ", cols=" << cols << ",rows=" << rows << endl
        << "centroX01=" << centroX01 << ",centroY01=" << centroY01 << endl
        << "angle=" << angle << endl
        << "depth_min=" << depth_min << ",depth_dif=" << depth_dif << ", frame number=" << ofGetFrameNum() << endl
        << "rnd=" <<  endl;
        
        ofSetColor(255, 255, 255,255);
        ofDrawBitmapString(reportScreen.str(), 400, 20);
    }
    
//     ofBackground(0, 0, 0);
//      drawBuffer();
}

void kinectShadowHand::keyPressed(int key) {
    switch (key) {
        case 'c':
            //            clear();
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case 'h':
            //            highlight = !highlight;
            break;
        case 'g':
            break;
        case 'p':
            break;
            
            //-------------------------
            // for kinect by kuha
        case '1':
            //            break;
        case '2':
            break;
        case 'b':
            break;
        case OF_KEY_RIGHT: // 0:far -> 255:near
            depth_min = min(depth_min + 1, 255);
            farThreshold03 = depth_min;
            nearThreshold03 = farThreshold03 + depth_dif;
            farThreshold02 = nearThreshold03;
            nearThreshold02 = farThreshold02 + depth_dif;
            farThreshold01 = nearThreshold02;
            nearThreshold01 = farThreshold01 + depth_dif;
            break;
        case OF_KEY_LEFT:
            depth_min = max(depth_min - 1, 0);
            farThreshold03 = depth_min;
            nearThreshold03 = farThreshold03 + depth_dif;
            farThreshold02 = nearThreshold03;
            nearThreshold02 = farThreshold02 + depth_dif;
            farThreshold01 = nearThreshold02;
            nearThreshold01 = farThreshold01 + depth_dif;
            break;
        case 'W':
            //            fullScreenRatio = min(fullScreenRatio + 0.01, 2.5);
            break;
        case 'w':
            //            fullScreenRatio = max(fullScreenRatio - 0.01, 1.0);
            break;
        case 'I':
            getInfo = getInfo * (-1);
            break;
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
            //-------------------------
            
        default:
            break;
    }
}

//--------------------------------------------------------------
// kinect exit
void kinectShadowHand::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
}


//--------------------------------------------------------------

