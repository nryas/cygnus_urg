#pragma once

#include "ofMain.h"
#include "urg.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
    private:
        Urg urg;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofxPanel gui;
        ofxFloatSlider sliderScale;
        ofxFloatSlider sliderX;
        ofxFloatSlider sliderY;
        ofxFloatSlider sliderR;
        ofxFloatSlider sliderD;
        ofxIntSlider soundSensitiveness;
    
        string sound_names[6];
        int last_feet_count;
        vector <ofSoundPlayer> sound_player;
        bool show_sensor_circle;
        bool show_gui;
};
