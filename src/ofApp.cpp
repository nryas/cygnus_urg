#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(false);
    ofBackground(0);
    
    urg.setMode(ofx::Urg::DISTANCE);
    urg.setupSerial();
    
    ofLogNotice("Product", urg.productType());
    ofLogNotice("Serial", urg.serialId());
    ofLogNotice("Status", urg.status());
    ofLogNotice("State", urg.state());
    ofLogNotice("Firmware version", urg.firmwareVersion());
    
    gui.setup();
    gui.add(sliderScale.setup("Scale", 1.49, 0.01, 3));
    gui.add(sliderX.setup("X", 460, -1000, 1000));
    gui.add(sliderY.setup("Y", -70, -1000, 1000));
    gui.add(sliderR.setup("R", 100, 0, 200));
    gui.add(sliderD.setup("D", 0, -2, 2));
    
    urg.start();
}

//--------------------------------------------------------------
void ofApp::update(){
    urg.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(sliderX, sliderY);
    ofRotateX(180);
    ofRotateZ(-96);
    ofScale(sliderScale, sliderScale, sliderScale);
    urg.drawData(sliderR, sliderD);
//  urg.drawDebugPolar();
    ofPopMatrix();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 0), 20, 140);
    if (!urg.isFrameCaptured()) {
        ofDrawBitmapString("frame is not captured", 20, 160);
    } else {
        ofDrawBitmapString("frame is captured", 20, 160);
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        urg.captureData();
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
