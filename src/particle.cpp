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
}

void Particle::draw() {
    ofSetColor(255, 255, 255);
    ofCircle(position, radius);
}

void Particle::update() {
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