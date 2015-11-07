//
//  particle.hpp
//  cygnus_urg
//
//  Created by Noriyasu Obushi on 2015/11/07.
//
//

#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>

#endif /* particle_hpp */

float radius = 40;

class Particle {
    
    public:
        void setup();
        void update();
        void draw();
        float remain_time;

};