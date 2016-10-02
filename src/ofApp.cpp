#include "ofApp.h"

//#define RBOID 100
#define BOID1 400
//#define GBOID 50
#define BOID2 300
//#define BBOID 25
#define BOID3 100
#define BOID4 100

#define BGCOLORn ofColor(0,0,0,20) // black
//#define BGCOLORd ofColor(32,210,200,50); //
#define BGCOLORd ofColor(32,178,170,50); // Emerald Green
//#define BGCOLORd ofColor(0,150,150,20); //

#define SDWCOLOR1n ofColor(255,0,0,20) // red
#define SDWCOLOR2n ofColor(0,0,255,20); // blue
#define SDWCOLOR1d ofColor(255,255,0,200) //
#define SDWCOLOR2d ofColor(255,128,10,200); //

#define COLOR1n ofColor(255,0,0,255) // red
#define COLOR2n ofColor(0,255,0,255)  // green
#define COLOR3n ofColor(0,255,255,255) //cyan
#define COLOR4n ofColor(255,255,0,255) // yellow
#define COLOR5n ofColor(255,165,0,255) //orange

#define COLOR1d ofColor(255,0,0,255) // red
#define COLOR2d ofColor(0,255,95,255)  // light Green
//#define COLOR2d ofColor(76,103,51,255)  // Ivy Green
//#define COLOR2d ofColor(255,0,255,255)  // mazenta
#define COLOR3d ofColor(100,0,255) // blue
#define COLOR4d ofColor(255,255,0,255) // Yellow
#define COLOR5d ofColor(255,165,0,255) //orange

#define FRATE 60

int mm; // present minute
int hh; // present hour
int ss; // present second
bool nightmode;

#define SOUDLIMIT 0.1
#define BALLMAX 300
#define NIGHT_START 18
#define DAY_START 8

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofToggleFullscreen();
    ofSetFrameRate(FRATE);
    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofSetRectMode(OF_RECTMODE_CORNER);

    ofEnableAlphaBlending();
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableSmoothing();
//        glEnable(GL_BLEND);
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    
    ofSetBackgroundColor(0,0,0);
    //    ofSetBackgroundColor(255,255,255);
    ofSetBackgroundAuto(false);
    //	ofSetBackgroundAuto(true);
    ofSetCircleResolution(64);
    
    ofHideCursor();
    
    //    bgcolor = ofColor(32,178,170,32); // Emerald Green
    bgcolor = BGCOLORn;
    ofSetBackgroundColor(bgcolor);
   
//    ofBackground(0, 0, 0);
    ofSetWindowTitle("kingyoid");
    
    shadowHand.setup();
    
// Boids
    ballsNum = 7;
    counterBall = 0;
    
//    hh = ofGetHours();
    hh = 0;
    setNightMode(hh);
    setColorDayNight();
    
    // self, enemy, friend1, friend2
    birds1.reserve(BOID1);
    for(int i = 0; i < BOID1; i++)
    {
        birds1.push_back(*new Bird( &birds1, i, color1, &birds2, &birds3, &nullBirds));
    }
    
    birds2.reserve(BOID2);
    for(int i = 0; i < BOID2; i++)
    {
        birds2.push_back(*new Bird( &birds2, i, color2, &nullBirds, &birds3, &nullBirds));
    }
    
    birds3.reserve(BOID3);
    for(int i = 0; i < BOID3; i++)
    {
        birds3.push_back(*new Bird( &nullBirds, i, color3, &nullBirds, &birds2, &nullBirds));
    }
    
    birds4.reserve(BOID4);
    for(int i = 0; i < BOID4; i++)
    {
        birds4.push_back(*new Bird( &birds4, i, color4, &birds1, &birds3, &nullBirds));
    }

    /*
   	soundStream.printDeviceList();
    //   soundStream.setup(this, 0, 1, 44100, 256, 4);
    soundStream.setup(this, 0, 1, 44100, 128, 4);
*/
    

}

//--------------------------------------------------------------
void ofApp::update(){

    shadowHand.update();

    // Boids
    for(int i = 0; i < balls.size(); i++)
    {
        if(balls[i].visible) balls[i].update();
    }
    
    for(int i = 0; i < birds1.size(); i++)
    {
        birds1[i].update();
    }
    
    for(int i = 0; i < birds2.size(); i++)
    {
        birds2[i].update();
    }
    
    for(int i = 0; i < birds3.size(); i++)
    {
        birds3[i].update();
     //   birds3[i].update();
    }
    
    for(int i = 0; i < birds4.size(); i++)
    {
        birds4[i].update();
//        birds4[i].update();
//        birds4[i].update();
    }
    
    
    for(int i = 0; i < balls.size(); i++)
    {
        if(balls[i].visible){
            for(int j = 0; j < birds1.size(); j++)
            {
                switch ( balls[i].fish )
                {
                    case 1 :
                        birds1[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 2 :
                        birds2[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 3 :
                        birds3[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 4 :
                        birds4[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 5 :
                        birds1[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        birds4[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                }
            }
        }
    }
  
    mm = ofGetMinutes();
    ss = ofGetSeconds();
/*
    if( mm % 10 < 1 && ss < 1) {
//        counterBall++;
        //        cout << ofGetFrameNum() << endl;
        //        cout << counterBall << endl;
//        if(counterBall % 3 == 0) ballGenerate( ofPoint( ofRandom(0, ofGetWidth()), ofRandom( 0, ofGetHeight())),0);

        //hh = ofGetHours();
        //setNightMode(hh);
        //setColorDayNight();
    }
*/
    //if(  ) {
    if( ss % 3 < 1 && ofGetFrameNum() % (FRATE / 2 ) < 1) {
        for(int i = 0; i < shadowHand.nCentroid; i++)
        {
            if( shadowHand.posCentroid[i].length() > 0 )
                ballGenerate(shadowHand.posCentroid[i], ofRandom(30, 100));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    shadowHand.draw();
    
// Boids
//    ofScale((float)kinect.width/ofGetWidth(), (float)kinect.height/ofGetHeight());
//    ofScaleMode(OF_SCALEMODE_CENTER);

    ofSetRectMode(OF_RECTMODE_CENTER);
    //    ofSetColor(0,0,0,32);
    //    ofSetColor(255,255,255,32);
    ofSetColor(bgcolor);
    ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(),ofGetHeight() );
    
    for(int i = 0; i < balls.size(); i++)
    {
        if(balls[i].visible) balls[i].draw();
    }
    
    for(int i = 0; i < birds1.size(); i++)
    {
        birds1[i].draw();
    }
    for(int i = 0; i < birds2.size(); i++)
    {
        birds2[i].draw();
    }
    for(int i = 0; i < birds3.size(); i++)
    {
        birds3[i].draw();
    }
    for(int i = 0; i < birds4.size(); i++)
    {
        birds4[i].draw();
    }
    
    //    cout << curVol << endl;
    /*
    if( curVol > SOUDLIMIT) {
        //        cout << curVol << endl;
        ballGenerate( ofPoint( ofRandom(0, ofGetWidth()), ofRandom( 0, ofGetHeight())), curVol * BALLMAX);
        counterBall = 0;
    }
*/
    
}

/*
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    curVol = 0.0;
    
    // samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        curVol += input[i] * input[i];
    }
    
    //this is how we get the mean of rms :)
    curVol /= bufferSize;
}
*/

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
//            active = !active;
            break;
        case 'f':
            ofToggleFullscreen();
            shadowHand.setup();
            break;
        case 'h':
            ofHideCursor();
            break;
        case 's':
            ofShowCursor();
            break;
        case 'n':
            nightmode = true;
            setColorDayNight();
            break;
        case 'd':
            nightmode = false;
            setColorDayNight();
            break;
        case 'c':
            balls.clear();
            break;
        case 'S':
//            soundStream.start();
            break;
        case 'E':
//            soundStream.stop();
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
            shadowHand.keyPressed(OF_KEY_RIGHT);
            break;
        case OF_KEY_LEFT:
            shadowHand.keyPressed(OF_KEY_LEFT);
            break;
        case 'W':
            //            fullScreenRatio = min(fullScreenRatio + 0.01, 2.5);
            break;
        case 'w':
            //            fullScreenRatio = max(fullScreenRatio - 0.01, 1.0);
            break;
        case 'I':
            shadowHand.keyPressed('I');
            break;
        case OF_KEY_UP:
            shadowHand.keyPressed(OF_KEY_UP);
            break;
        case OF_KEY_DOWN:
            shadowHand.keyPressed(OF_KEY_DOWN);
            break;
            //-------------------------
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_pressed = true;
    //    myball.visible = true;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouse_pressed = false;
    ballGenerate(ofPoint(x,y),0);

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void ofApp::ballGenerate(ofPoint _pos, float _radius){
    if( ballsNum <= balls.size() )
    {
        balls.erase(balls.begin());
    }
    Ball b;
    b.pos = _pos;
    if(_radius > 0.9 ) b.radius = _radius;
    int f = ofRandom(1,6);
    switch ( f )
    {
        case 1: b.bcolor = color1; b.fish = 1; break;
        case 2: b.bcolor = color2; b.fish = 2; break;
        case 3: b.bcolor = color3; b.fish = 3; break;
        case 4: b.bcolor = color4; b.fish = 4; break;
        case 5: b.bcolor = color5; b.fish = 5; break;
    }
    balls.push_back(b);
    counterBall = 0;
}

//--------------------------------------------------------------
void ofApp::setColorDayNight(){
    if( nightmode ){
        bgcolor = BGCOLORn; // Black
        color1 = COLOR1n;
        color2 = COLOR2n;
        color3 = COLOR3n;
        color4 = COLOR4n;
        color5 = COLOR5n;
        
        shadowHand.shadwColor01 = SDWCOLOR1n;
        shadowHand.shadwColor02 = SDWCOLOR2n;
    }
    else{
        bgcolor = BGCOLORd;
        color1 = COLOR1d;
        color2 = COLOR2d;
        color3 = COLOR3d;
        color4 = COLOR4d;
        color5 = COLOR5d;

        shadowHand.shadwColor01 = SDWCOLOR1d;
        shadowHand.shadwColor02 = SDWCOLOR2d;
}
    
    for(int i = 0; i < birds1.size(); i++)
    {
        birds1[i].circleColor = color1;
    }
    for(int i = 0; i < birds2.size(); i++)
    {
        birds2[i].circleColor = color2;
    }
    for(int i = 0; i < birds3.size(); i++)
    {
        birds3[i].circleColor = color3;
    }
    for(int i = 0; i < birds4.size(); i++)
    {
        birds4[i].circleColor = color4;
    }
    
    for(int i = 0; i < balls.size(); i++)
    {
        switch ( balls[i].fish )
        {
            case 1: balls[i].bcolor = color1; break;
            case 2: balls[i].bcolor = color2; break;
            case 3: balls[i].bcolor = color3; break;
            case 4: balls[i].bcolor = color4; break;
            case 5: balls[i].bcolor = color5; break;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::setNightMode(int h){
    if( h < DAY_START || h >= NIGHT_START ){
        nightmode = true;
    }
    else {
        nightmode = false;
    }
}


