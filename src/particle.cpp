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
    radius = 60;
    speed = ofPoint(0, 0);
    phase_speed = ofRandom(0.1, 0.5);
    phase = 0;
}

void Particle::draw() {
    ofSetColor(255, 255, 255);
    ofCircle(position, radius);
}

void Particle::update() {
    radius = radius * sin(phase);
    phase += phase_speed;
//    if(phase > TWO_PI) {
//        phase -= TWO_PI;
//    }
    
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