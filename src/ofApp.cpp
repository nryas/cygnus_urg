#include "ofApp.h"
#include "ofxSPK.h"

ofxSPK::System sys;
ofxSPK::Group group;
ofImage sprite;
ofxSPK::Modifier rot;

bool sound_end(ofSoundPlayer sp) {
    return !sp.getIsPlaying();
}

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
    gui.add(sliderScale.setup("Scale", 0.2492, 0.01, 3));
    gui.add(sliderX.setup("X", 550, -1000, 1000));
    gui.add(sliderY.setup("Y", -10, -1000, 1000));
    gui.add(sliderR.setup("R", 100, 0, 200));
    gui.add(sliderD.setup("D", 0, -2, 2));
    gui.add(soundSensitiveness.setup("S", 4, 1, 20));
    
    urg.start();
    
    // setup pointsprite texture
    // NOTES: the texture size must be Power of Two,
    // and turn off arb texture option while loading
    ofDisableArbTex();
    sprite.loadImage("image.jpg");
    ofEnableArbTex();
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    sys.setup();
    
    group.setup(sys);
    group.setColor(ofxSPK::RangeC(ofColor(255, 255), ofColor(255, 255)),
                   ofxSPK::RangeC(ofColor(0, 0), ofColor(255, 0)));
    
    group.setLifeTime(1, 20);
    group.setFriction(0.1);
    group.setSize(0, ofxSPK::RangeF(30, 250));
    
    group.setGravity(ofVec3f(0, 0, 0));
    group.setMass(0.1, 1);
    
    rot.setup(SPK::Vortex::create(SPK::Vector3D(ofGetWidth()/2, ofGetHeight()/2),
                                  SPK::Vector3D(0, 0, 0),
                                  200,
                                  10), group);
    
    group.reserve(400);
    
    last_feet_count = 0;
    
    show_gui = show_sensor_circle = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    urg.update(sliderR, sliderD);

    for (int i=0; i<urg.feet.size(); i++) {
        group.emitRandom(10, ofVec3f(urg.feet[i]->x, urg.feet[i]->y));
        sys.update();
    }
    
//    printf("%d\n", (int)std::fabs(last_feet_count - (int)urg.feet.size()));
    
    printf("%d\n", (int)sound_player.size());
    if (std::fabs(last_feet_count - (int)urg.feet.size()) > soundSensitiveness) {
        ofSoundPlayer sp;
        sp.loadSound("cygnus0"+ofToString((int)ofRandom(5)+1)+".mp3");
        sp.setLoop(false);
        sp.setMultiPlay(false);
        sp.play();
        sound_player.push_back(sp);
    }
    last_feet_count = urg.feet.size();
    
    sound_player.erase(remove_if(sound_player.begin(), sound_player.end(), sound_end), sound_player.end());

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(sliderX, sliderY);
    ofRotateX(180);
    ofRotateZ(-96);
    ofScale(sliderScale, sliderScale, sliderScale);
    
    if (show_sensor_circle) {
        urg.draw();
    }
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
//     sys.debugDraw();
    
    // bind texture, enable point sprite while drawing particles
    sprite.bind();
    ofEnablePointSprites();
    sys.draw();
    ofDisablePointSprites();
    sprite.unbind();
    
    if (show_gui) {
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        urg.captureData();
    } else if (key == 'd') {
        show_gui = !show_gui;
        show_sensor_circle = !show_sensor_circle;
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
