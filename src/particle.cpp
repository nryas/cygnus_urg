//
//  particle.cpp
//  cygnus_urg
//
//  Created by Noriyasu Obushi on 2015/11/07.
//
//

#include "particle.hpp"

Particle::Particle() {
    position = ofPoint(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
    radius = ofRandom(30, 60);
    speed = ofPoint(0, 0);
    phase_speed = ofRandom(0.1, 0.5);
    phase = 0;
}

void Particle::draw() {
    ofSetColor(200, 20, 20, 100);
    ofNoFill();
    ofCircle(position, radius);
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofCircle(position.x, position.y, radius/10.0);
    ofSetColor(200, 20, 20);
}

void Particle::update() {
    radius = radius + sin(phase)*radius/4;
    phase += phase_speed;
    if(phase > TWO_PI) {
        phase -= TWO_PI;
    }
    
    if (position.x < radius || position.x > ofGetWidth() - radius) {
        speed.x *= -1;
    }
    
    if (position.y < radius || position.y > ofGetHeight() - radius) {
        speed.y *= -1;
    }
}

void Particle::setPos(ofPoint _position) {
    position = _position;
}

ofPoint Particle::getPos() {
    return position;
}

void Particle::setRadius(float _radius) {
    radius = _radius;
}

float Particle::getRadius() {
    return radius;
}

void Particle::setSpeed(ofPoint _speed) {
    speed = _speed;
}

ofPoint Particle::getSpeed() {
    return speed;
}