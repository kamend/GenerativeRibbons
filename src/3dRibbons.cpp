//
//  3dRibbons.cpp
//  emptyExample
//
//  Created by Dimitrov Kamen on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "3dRibbons.h"
#include "ofMain.h"

RibbonCurve::RibbonCurve(ofVec3f _startPoint, ofVec3f _endPoint, ofVec3f _controlPoint, float _ribbonWidth, float _resolution, float _color) {
    
    startPoint = _startPoint;
    endPoint = _endPoint;
    controlPoint = _controlPoint;
    
    ribbonWidth = _ribbonWidth;
    resolution = _resolution;
    color = _color;   
    
    stepId = 0;
    
}

void RibbonCurve::addSegment() {
    
    float t = stepId / resolution;
    
    ofVec3f p0 = getOffsetPoint(t, 0);
    ofVec3f p3 = getOffsetPoint(t, ribbonWidth);
    
    stepId ++;
    if(stepId > resolution) return;
    
    t = stepId / resolution;
 
    ofVec3f p1 = getOffsetPoint(t, 0);
    ofVec3f p2 = getOffsetPoint(t, ribbonWidth);
    
    Quad q;
    q.p1 = p0;
    q.p2 = p1;
    q.p3 = p2;
    q.p4 = p3;
    quads.push_back(q);

}

void RibbonCurve::removeSegment() {
    if(quads.size() > 1) {
        quads.pop_front();
    }
}

ofVec3f RibbonCurve::getOffsetPoint(float t, float k) {
    
    ofVec3f p0 = startPoint;
    ofVec3f p1 = controlPoint;
    ofVec3f p2 = endPoint;
    
    
    //-- x(t), y(t)
    float xt = ( 1 - t ) * ( 1 - t ) * p0.x + 2 * t * ( 1 - t ) * p1.x + t * t * p2.x;
    float yt = ( 1 - t ) * ( 1 - t ) * p0.y + 2 * t * ( 1 - t ) * p1.y + t * t * p2.y;
    float zt = ( 1 - t ) * ( 1 - t ) * p0.z + 2 * t * ( 1 - t ) * p1.z + t * t * p2.z;

    //-- x'(t), y'(t)
    float xd = t*(p0.x - 2*p1.x + p2.x) - p0.x + p1.x;
    float yd = t*(p0.y - 2*p1.y + p2.y) - p0.y + p1.y;
    float zd = t*(p0.z - 2*p1.z + p2.z) - p0.z + p1.z;
    float dd = pow( xd * xd + yd * yd + zd * zd,1/3); 
    
    return ofVec3f(xt + ( k * yd ) / dd, yt - ( k * xd ) / dd, zt - ( k * xd ) / dd);
}


// class Ribbon

Ribbon::Ribbon() {
    stepId = 0;
    
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 100);
    
    points.push_back(getRandomPoint(ofVec3f(0,0,0), 0));
    points.push_back(getRandomPoint(ofVec3f(0,0,0), 0));
    points.push_back(getRandomPoint(ofVec3f(0,0,0), 0));

}

void Ribbon::update(ofVec3f target, float separation) {
    if(curves.size() < 1) {
        // add the very first ribbon and continue
        AddRibbonCurve(target, separation);
        return;
    }
    
    
    // add segment to the current ribbon
    currentCurve->addSegment();
    
    int size = curves.size();
    if(size > CURVE_RESOLUTION -1 ) {
        // if we have reached enough number of curves in the ribbon
        // we start removing segments from the curve at the front
        
        RibbonCurve *curve = curves.front();
        curve->removeSegment();
    }
    
    // 
    stepId++;
    
    // if we have inserted enough segments
    // we insert a new Curve
    if(stepId > RIBBON_RESOLUTION) AddRibbonCurve(target, separation);    
}

void Ribbon::draw() {
    
    ofMesh m;
    m.setMode(OF_PRIMITIVE_TRIANGLES);
    
    int j=0;
    for (std::list<RibbonCurve*>::const_iterator iterator = curves.begin(), end = curves.end(); iterator != end; ++iterator) {   
        RibbonCurve* rCurve = *iterator;
       
        for (std::list<Quad>::const_iterator iterator = rCurve->quads.begin(), end = rCurve->quads.end(); iterator != end; ++iterator) {
            Quad q = *iterator;
            
            m.addVertex(q.p1);
            m.addColor(color);
            j++;
            m.addVertex(q.p4);
            m.addColor(color);
            j++;
                        
            if(j > 2) {
                m.addTriangle(j - 4 , j-3, j-2);
                m.addTriangle(j - 3 , j-1, j - 2);
            }
        }    
    
    }
    
    m.drawFaces();
}

void Ribbon::AddRibbonCurve(ofVec3f _t,float _sep) {

    points.push_back(getRandomPoint(_t, _sep));
    
    ofVec3f nextPoint = points.at(points.size()-1);
    ofVec3f curPoint = points.at(points.size()-2);
    ofVec3f lastPoint = points.at(points.size()-3);
    
    ofVec3f lastMidPoint = ofVec3f((curPoint.x + lastPoint.x)/2
                            ,(curPoint.y + lastPoint.y)/2
                            ,(curPoint.z + lastPoint.z)/2);
    ofVec3f midPoint = ofVec3f((curPoint.x + nextPoint.x)/2,
                                (curPoint.y + nextPoint.y)/2,
                                   (curPoint.z + nextPoint.z)/2);
    
    currentCurve = new RibbonCurve(lastMidPoint, midPoint,curPoint, RIBBON_WIDTH, RIBBON_RESOLUTION, 0);
    curves.push_back(currentCurve);
    
    if(curves.size() > CURVE_RESOLUTION) {
        // if we have more then enough curves, we remove the curve at the front
        RibbonCurve *curveToDelete = curves.front();
        curves.pop_front();
        delete curveToDelete;
    }
    
    stepId = 0;
    
}

ofVec3f Ribbon::getRandomPoint(ofVec3f target, float separation) {
    return ofVec3f (target.x + ofRandom(-separation, separation), target.y + ofRandom(-separation, separation),
                    target.z + ofRandom(-separation, separation));
}


