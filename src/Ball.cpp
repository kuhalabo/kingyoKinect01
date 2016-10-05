//
//  Ball.cpp
//  kingyoKinect01
//
//  Created by kuha on 2016/09/30.
//
//

#include "Ball.hpp"

Ball::Ball(){
    pos = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    vel = ofVec2f(ofRandom(-0.8,0.8),ofRandom(-0.8,0.8));
    acc = ofVec2f(0,0);
    radius = 100;
    fish = 1;
    visible = true;
}
Ball::~Ball(){}

void Ball::update(){
    acc = ofVec2f(ofRandom(-0.1,0.1),ofRandom(-0.1,0.1));
    vel += acc;
    if( vel.length() > 1 ) {
        vel.scale(0.75);
    }
    pos += vel;
    
    if( pos.x > ofGetWidth() || pos.x < 0 ){
        vel.x *= -1;
    }
    if( pos.y > ofGetHeight() || pos.y < 0 ){
        vel.y *= -1;
    }
    if( (ofGetFrameNum() % 60 ) == 0 ) radius *= 0.97;
    if(radius < 40.0) {
        visible = false;
    }
}

void Ball::draw(){
    //    ofSetColor(bcolor);
    //    ofNoFill();
    
    int radius2 = radius * ofRandom(1.0,1.5);
    //    ofSetColor(231, 227, 255, 10);
    ofSetColor(bcolor.r, bcolor.g, bcolor.b, 10);
    ofDrawCircle(pos, radius2);
    //    ofSetColor(231, 227, 255, 30);
    ofSetColor(bcolor.r, bcolor.g, bcolor.b, 20);
    ofDrawCircle(pos, radius2 * 0.75);
    //    ofFill();
    //    ofRotateX(5);
    //    ofRect(pos, radius2 * 0.75, radius2 * 0.75);
    //    ofSetColor(231, 227, 255, 80);
    ofSetColor(bcolor.r, bcolor.g, bcolor.b, 30);
    ofDrawCircle(pos, radius * 0.3);
}
