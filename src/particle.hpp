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

#endif /* particle_hpp */

class Particle {
    
    private:
        ofPoint position;
        ofPoint speed;
        float radius;
        float phase;
        float phase_speed;
    
    public:
        Particle();
        void setup();
        void update();
        void draw();
        void setPos(ofPoint _position);
        ofPoint getPos();
        void setRadius(float _radius);
        float getRadius();
        void setSpeed(ofPoint _speed);
        ofPoint getSpeed();

};