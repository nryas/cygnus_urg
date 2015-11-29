#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(false);
    ofBackground(0);
    
    unsigned w = 1000;
    unsigned h = 1000;
    particles.init(w, h);
    
    // initial positions
    // use new to allocate 4,000,000 floats on the heap rather than
    // the stack
    float* particlePos = new float[w * h * 4];
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
            unsigned idx = y * w + x;
            particlePos[idx * 4] = 400.f * x / (float)w - 200.f; // particle x
            particlePos[idx * 4 + 1] = 400.f * y / (float)h - 200.f; // particle y
            particlePos[idx * 4 + 2] = 0.f; // particle z
            particlePos[idx * 4 + 3] = 0.f; // dummy
        }
    }
    particles.loadDataTexture(ofxGpuParticles::POSITION, particlePos);
    delete[] particlePos;
    
    // initial velocities
    particles.zeroDataTexture(ofxGpuParticles::VELOCITY);
    
    // listen for update event to set additonal update uniforms
    ofAddListener(particles.updateEvent, this, &ofApp::onParticlesUpdate);
    
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

void ofApp::onParticlesUpdate(ofShader& shader) {
    ofVec3f mouse(ofGetMouseX() - .5f * ofGetWidth(), .5f * ofGetHeight() - ofGetMouseY(), 0.f);
    shader.setUniform3fv("mouse", mouse.getPtr());
    shader.setUniform1f("elapsed", ofGetLastFrameTime());
    shader.setUniform1f("radiusSquared", 200.f * 200.f);
}

//--------------------------------------------------------------
void ofApp::update(){
    particles.update();
    urg.update(sliderR, sliderD);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(sliderX, sliderY);
    ofRotateX(180);
    ofRotateZ(-96);
    ofScale(sliderScale, sliderScale, sliderScale);
    
    urg.draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    particles.draw();
    ofDisableBlendMode();
    
//  urg.drawDebugPolar();
    ofPopMatrix();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 0), 20, 140);
    if (!urg.isFrameCaptured()) {
        ofDrawBitmapString("not learned", 20, 160);
    } else {
        ofDrawBitmapString("learned", 20, 160);
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
