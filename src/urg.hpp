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

#endif /* urg_hpp */

using ofxUrg::Device;
class Urg : public Device{
    protected:
        bool is_frame_captured;
        vector<long> data_captured, data_diff;
    
    public:
        Urg();
        void captureData();
        void drawData();
        void update();
        bool isFrameCaptured();
};