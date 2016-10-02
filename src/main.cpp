#include "ofMain.h"
#include "ofApp.h"

//#include "kinectShadowHand.hpp"

//========================================================================
int main( ){
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    ofSetupOpenGL(800,600,OF_WINDOW);			// <-------- setup the GL context
//    ofSetupOpenGL(640,480,OF_WINDOW);			// <-------- setup the GL context
//    ofSetupOpenGL(1280,960,OF_WINDOW);			// <-------- setup the GL context
//    ofSetupOpenGL(1280,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
    //ofRunApp(new kinectShadowHand());

}
