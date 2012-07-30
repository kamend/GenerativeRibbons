#pragma once

#include "ofMain.h"
#include "ofxNoise.h"
#include "3dRibbons.h"
#include "ofxFX.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofxPerlin perlin;
    float zValue;
    float radiusValue;
    float colorsValue;
    
    vector<Ribbon*> ribbons;
    
    ofxBlur blur;
    ofxBloom bloom;
    ofxGlow glow;
};
