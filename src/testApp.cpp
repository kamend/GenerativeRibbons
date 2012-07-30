#include "testApp.h"

const int numRibbons = 30;

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);  
    
      
    zValue = ofRandom(5,10);
    radiusValue = ofRandom(5,10);
    colorsValue = ofRandom(1,10);
  
    for(int i=0;i<numRibbons;i++) {
        Ribbon *r = new Ribbon();
        
        
        
        ribbons.push_back(r);
    }
    
    blur.allocate(ofGetWidth(), ofGetHeight());
    blur.setRadius(10.0);
    bloom.allocate(ofGetWidth(), ofGetHeight());
    glow.allocate(ofGetWidth(), ofGetHeight());
   
}

//--------------------------------------------------------------
void testApp::update(){
    
    ofVec3f target = ofVec3f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(100));
    float sep = 200*perlin.noiseuf(zValue);
    for(int i=0;i<numRibbons;i++) {
     
        ribbons[i]->color = ofColor(ofMap(i, 0, numRibbons, 0, 255),255*perlin.noiseuf(colorsValue),200,ofMap(i, 0, numRibbons, 100, 200));
        ribbons[i]->update(target, sep);
         colorsValue += 0.0001;
    }
    
    zValue += 0.001;
    
   
}

//--------------------------------------------------------------
void testApp::draw(){
    
    blur.begin();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ofBackground(0, 0, 0);

    for(int i=0;i<numRibbons;i++) {
        ribbons[i]->draw();
    }   
    
    blur.end();
    
    blur >> bloom >> glow;
    
    glow.setRadius(15.0);
    
    blur.update();
  
    bloom.update();
    glow.update();
    
    glow.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}