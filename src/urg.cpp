//
//  urg.cpp
//  cygnus_urg
//
//  Created by Noriyasu Obushi on 2015/11/08.
//
//

#include "urg.hpp"

#include "ofxSPK.h"

ofxSPK::System sys;
ofxSPK::Group group;

ofImage sprite;

ofxSPK::Modifier rot;

Urg::Urg() {
    is_frame_learned = false;
    streak_count = 0;
    total = 0;
    
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
    
    group.setLifeTime(0.5, 5);
    group.setFriction(0.1);
    group.setSize(0, ofxSPK::RangeF(30, 250));
    
    group.setGravity(ofVec3f(0, -10, 0));
    group.setMass(0.1, 1);
    
    rot.setup(SPK::Vortex::create(SPK::Vector3D(ofGetWidth()/2, ofGetHeight()/2),
                                  SPK::Vector3D(0, 1, 0),
                                  200,
                                  10), group);
    
    group.reserve(10000);
}

void Urg::captureData(){
    data_captured = data_buffer;
    is_frame_learned = true;
}

void Urg::update(float sliderR, float sliderD) {
    
    feet.clear();
    
    if (is_frame_learned)
    {
        
        for (int i=0; i<streak_end.size(); i++) {
            float r = data_diff[streak_end[i]];
            float theta = urg.index2rad(streak_end[i]);
            float x = r * cos(theta);
            float y = r * sin(theta);
            
            if (abs(x), abs(y) > 1) {
                shared_ptr<ofPoint> foot = shared_ptr<ofPoint>(new ofPoint(x, y));
                feet.push_back(foot);
            }
        }
    }
    
    is_frame_new = false;
    
    ofMutex mutex;
    mutex.lock();
    if (data != data_buffer)
    {
        streak_end.clear();
        data_diff = data_buffer;
        if (is_frame_learned) {
            for (int i=0; i<data_diff.size(); i++) {
                
                if (abs(data_captured[i] - data_diff[i]) < 100) {
                    data_diff[i] = 0;
                }
                
                if (streak_count >= 5) {
                    for (int j=i-streak_count; j<i; j++)
                        total += data_diff[j];
                    
                    float moving_ave = total / streak_count;
                    
                    if (data_diff[i]/moving_ave > 0.7 && data_diff[i]/moving_ave < 1.3 && data_diff[i] != 0) {
                        streak_count++;
                    } else {
                        streak_end.push_back(i);
                        streak_count = 0;
                    }
                } else {
                    if (data_diff[i] == 0)
                        streak_count = 0;
                    else
                        streak_count++;
                }
            }
        }
        data = data_buffer;
        is_frame_new = true;
    }
    
    if (mode == ofxUrg::DISTANCE_INTENSITY || mode == ofxUrg::MULTIECHO_INTENSITY)
    {
        if (intensity != intensity_buffer)
        {
            intensity = intensity_buffer;
            is_frame_new = true;
        }
    }
    mutex.unlock();
    
    group.emitRandom(10, ofVec3f(ofGetMouseX(), ofGetMouseY()));
    
    sys.update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void Urg::draw(){
    
    for (int i=0; i<data.size(); i++) {
        float r = 100;
        float theta = urg.index2rad(i);
        float x = r * cos(theta);
        float y = r * sin(theta);
        ofCircle(x, y, 10);
    }
    
    for (int i=0; i<feet.size(); i++) {
        ofCircle(feet[i]->x, feet[i]->y, 20);
    }
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // sys.debugDraw();
    
    // bind texture, enable point sprite while drawing particles
    sprite.bind();
    ofEnablePointSprites();
    sys.draw();
    ofDisablePointSprites();
    sprite.unbind();
}

bool Urg::isFrameCaptured() { return is_frame_learned; }