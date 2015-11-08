//
//  urg.cpp
//  cygnus_urg
//
//  Created by Noriyasu Obushi on 2015/11/08.
//
//

#include "urg.hpp"
Urg::Urg() {
    is_frame_captured = false;
}
void Urg::captureData(){
    data_captured = data_buffer;
    is_frame_captured = true;
}

void Urg::drawData(){
    ofNoFill();
    if (is_frame_captured)
    {
        for (int i=0; i<data_diff.size(); i++)
        {
            float r = data_diff[i];
            float theta = urg.index2rad(i);
            float x = r * cos(theta);
            float y = r * sin(theta);
            //                printf("data_diff[%3d]:%ld, x:%f, y:%f, t:%f\n", i, data_diff[i], r*cos(theta), r*sin(theta), theta);
            //                m.addVertex(ofVec3f(x,y));
            ofCircle(r*cos(theta), r*sin(theta), 100);
        }
    }
}

void Urg::update() {
    is_frame_new = false;
    
    ofMutex mutex;
    mutex.lock();
    if (data != data_buffer)
    {
        data_diff = data_buffer;
        if (is_frame_captured) {
            for (int i=0; i<data_captured.size(); ++i) {
//                printf("%d / data_diff:%ld / data_captured:%ld\n", i, data_diff[i], data_captured[i]);
                if (data_captured[i] != 0) {
                    if (data_captured[i] - data_diff[i] < 50) {
                        data_diff[i] = 0;
                    }
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
}

bool Urg::isFrameCaptured() { return is_frame_captured; }