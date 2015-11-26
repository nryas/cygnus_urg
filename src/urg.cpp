//
//  urg.cpp
//  cygnus_urg
//
//  Created by Noriyasu Obushi on 2015/11/08.
//
//

#include "urg.hpp"

#define MAX_DISTANCE 0
#define STREAK_END 20000

Urg::Urg() {
    is_frame_captured = false;
    streak_count = 0;
    total = 0;
}
void Urg::captureData(){
    data_captured = data_buffer;
    is_frame_captured = true;
}

void Urg::drawData(float sliderR, float sliderD){
    
    if (is_frame_captured)
    {
        for (int i=0; i<streak_end.size(); i++) {
            float r = data_diff[streak_end[i]];
            float theta = urg.index2rad(streak_end[i]);
            float x = r * cos(theta);
            float y = r * sin(theta);
            
            if (abs(x), abs(y) > 1) {
                Particle p;
                p.setPos(ofPoint(x + x * sliderD, y));
                p.setRadius(sliderR);
                p.setSpeed(ofPoint(1.2, 1.2));
                p.draw();
                particles.push_back(p);
            }
        }
        
        for (int i=0; i<data.size(); i++) {
            float r = 100;
            float theta = urg.index2rad(i);
            float x = r * cos(theta);
            float y = r * sin(theta);
            ofCircle(x, y, 10);
        }
    }
}

void Urg::update() {
    for (int i=0; i<particles.size(); i++) {
        if (particles[i].getRadius() == 0)
            particles.erase(particles.begin() + i);
        particles[i].update();
    }
    
    is_frame_new = false;
    
    ofMutex mutex;
    mutex.lock();
    if (data != data_buffer)
    {
        streak_end.clear();
        data_diff = data_buffer;
        if (is_frame_captured) {
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
}

bool Urg::isFrameCaptured() { return is_frame_captured; }