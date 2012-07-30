//
//  3dRibbons.h
//  emptyExample
//
//  Created by Dimitrov Kamen on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample__dRibbons_h
#define emptyExample__dRibbons_h

#include "ofMain.h"

#define RIBBON_WIDTH 0.03
#define RIBBON_RESOLUTION 45

#define CURVE_RESOLUTION 10


typedef struct Quad {
    ofVec3f p1,p2,p3,p4;
} Quad;

class RibbonCurve {
public:
    int stepId;
    ofVec3f startPoint, endPoint, controlPoint;
    float ribbonWidth;
    float resolution;
    float color;
    
    std::list<Quad> quads;
    
    RibbonCurve(ofVec3f _startPoint, ofVec3f _endPoint, ofVec3f _controlPoint, float _ribbonWidth, float _resolution, float _color);
    void addSegment();
    void removeSegment();
    ofVec3f getOffsetPoint(float t, float k);
};



class Ribbon {
public:
    int numCurves;
    std::list<RibbonCurve*> curves;
    RibbonCurve *currentCurve;
    int stepId;
    vector<ofVec3f> points;
    ofColor color;
    
    Ribbon();
    void draw();
    void update(ofVec3f target, float separation);
    void AddRibbonCurve(ofVec3f _t, float _sep);
    ofVec3f getRandomPoint(ofVec3f target, float separation);
        
    
};

#endif
