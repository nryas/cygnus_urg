#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    urg.setMode(ofxUrg::DISTANCE);
    urg.setupSerial();
    
    ofLogNotice("Product", urg.productType());
    ofLogNotice("Serial", urg.serialId());
    ofLogNotice("Status", urg.status());
    ofLogNotice("State", urg.state());
    ofLogNotice("Firmware version", urg.firmwareVersion());
    
    gui.setup();
    gui.add(slider.setup("Scale", 2.4, 0.01, 3));
    
    urg.start();
}

//--------------------------------------------------------------
void ofApp::update(){
    urg.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofPushMatrix();
    float s = slider;
    ofScale(s, s, s);
    
    ofRotateZ(-90);
    urg.drawData();
//            urg.drawDebugPolar();
    ofPopMatrix();
    cam.end();
    
    //        urg.drawData();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 0), 20, 80);
    if (!urg.isFrameCaptured()) {
        ofDrawBitmapString("frame is not captured", 20, 100);
    } else {
        ofDrawBitmapString("frame is captured", 20, 120);
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
