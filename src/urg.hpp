//
//  urg.hpp
//  cygnus_urg
//
//  Created by Noriyasu Obushi on 2015/11/08.
//
//

#ifndef urg_hpp
#define urg_hpp

#include "ofxUrg.h"
#include "particle.hpp"

#define CIRCLE_NUM 2000

#endif /* urg_hpp */

using ofxUrg::Device;
class Urg : public Device{
    protected:
        bool is_frame_learned;
        vector<long> data_captured, data_diff;
        vector<int> streak_end;
        int streak_count;
        long total;
    
    public:
        Urg();
        void captureData();
        void draw();
        void update(float sliderR, float sliderD);
        bool isFrameCaptured();
        vector <shared_ptr <ofxBox2dCircle> > feet;
        vector <shared_ptr <ofxBox2dCircle> > circles;
        ofxBox2d box2d;
};