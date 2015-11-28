//
//  particle.hpp
//  cygnus_urg
//
//  Created by Noriyasu Obushi on 2015/11/07.
//
//

#ifndef particle_hpp
#define particle_hpp

#include "ofMain.h"
#include "ofxBox2d.h"

#endif /* particle_hpp */

class Particle : public ofxBox2dCircle {
    
    private:
        ofPoint position;
        float radius;
    
    public:
        Particle();
        void setup();
        void update(Particle p);
        void draw();
    
        void setPos(ofPoint _position);
        ofPoint getPos();
    
        void setRadius(float _radius);
        float getRadius();
};