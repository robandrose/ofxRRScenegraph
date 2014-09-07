#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    renderer.setSize(ofGetWidth(), ofGetHeight());
    renderer.setupColorPicker(ofGetWidth(), ofGetHeight(), 2, 5);
    renderer.startTuio(3333);
    
    cont.enableDepthTest();
    for(int i=0;i<40;i++){
        buttons[i].setSize(100, 100);
        buttons[i].setPosition(ofRandomWidth(),ofRandomHeight());
        buttons[i].setColor(255, 0, 0);
        buttons[i].enableDepthTest();
        ofAddListener(buttons[i].tapEvent, this, &ofApp::onButtonTap);
        
        buttons[i].setRandomColor();
        cont.addChild(&buttons[i]);
        
    }
    
    renderer.addChild(&cont);
    
}

void ofApp::onButtonTap(MultiTouchEvent &e){
    e.target->moveTo(e.target->getX(), e.target->getY(), ofRandom(-500,500), 500);
    e.target->rotateTo(ofRandom(-60,60), 0, 0, 300);
}


//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    renderer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    renderer.resize();
    renderer.setupColorPicker(ofGetWidth(), ofGetHeight(), 2, 5);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}